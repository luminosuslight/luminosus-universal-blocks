#include "PerformanceMonitorBlock.h"

#include "core/connections/Nodes.h"
#include "core/manager/BlockList.h"


bool PerformanceMonitorBlock::s_registered = BlockList::getInstance().addBlock(PerformanceMonitorBlock::info());

static bool initialized = false;

#ifdef Q_OS_LINUX
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

void init() {
    FILE* file = fopen("/proc/stat", "r");
    if (!fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
                &lastTotalSys, &lastTotalIdle)) {
        qWarning() << "Couldn't access CPU usage values";
    }
    fclose(file);
}

double getCurrentCpuUsage() {
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    file = fopen("/proc/stat", "r");
    if (!fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
        &totalSys, &totalIdle)) {
        qWarning() << "Couldn't access CPU usage values";
    }
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return percent;
}
#else
void init() {
}

double getCurrentCpuUsage() {
    return 0.0;
}
#endif


PerformanceMonitorBlock::PerformanceMonitorBlock(CoreController* controller, QString uid)
    : OneOutputBlock(controller, uid)
    , m_cpuUsage(this, "cpuUsage", 0, 0, 1, /*persistent*/ false)
{
    if (!initialized) init();

    m_refreshTimer.setInterval(500);
    connect(&m_refreshTimer, &QTimer::timeout, this, &PerformanceMonitorBlock::updateCpuUsage);
    m_refreshTimer.start();
}

void PerformanceMonitorBlock::updateCpuUsage() {
    m_cpuUsage = getCurrentCpuUsage();
    m_outputNode->setValue(m_cpuUsage);
}
