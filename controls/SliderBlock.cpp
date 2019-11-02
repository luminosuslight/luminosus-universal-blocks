// Copyright (c) 2016 Electronic Theatre Controls, Inc., http://www.etcconnect.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
#include "SliderBlock.h"

#include "core/CoreController.h"
#include "core/connections/Nodes.h"
#include "core/helpers/utils.h"
#include "core/manager/BlockList.h"

bool SliderBlock::s_registered = BlockList::getInstance().addBlock(SliderBlock::info());

SliderBlock::SliderBlock(CoreController* controller, QString uid)
    : OneOutputBlock(controller, uid)
{
    m_heightIsResizable = true;
}

void SliderBlock::getAdditionalState(QJsonObject& state) const {
    state["value"] = getValue();
}

void SliderBlock::setAdditionalState(const QJsonObject &state) {
    setValue(state["value"].toDouble());
}

void SliderBlock::onControllerPressed() {
	m_valueBeforeFlash = getValue();
    if (getGuiItemChild("slider")) {
        getGuiItemChild("slider")->setProperty("value", m_valueBeforeFlash < 0.99 ? 1 : 0);
    } else {
        qWarning() << "FIXME: SliderBlock doesn't work without GUI!";
    }
    // TODO: create a more universal property for this
//	m_controller->powermate()->setBrightness(1.);
}

void SliderBlock::onControllerReleased(double) {
    if (getGuiItemChild("slider")) {
        getGuiItemChild("slider")->setProperty("value", m_valueBeforeFlash);
    } else {
        qWarning() << "FIXME: SliderBlock doesn't work without GUI!";
    }
//	m_controller->powermate()->setBrightness(m_valueBeforeFlash);
}

void SliderBlock::onControllerRotated(double relativeAmount, double, bool) {
    double newValue = getValue() + relativeAmount;
    if (getGuiItemChild("slider")) {
        getGuiItemChild("slider")->setProperty("value", limit(0., newValue, 1.));
    } else {
        qWarning() << "FIXME: SliderBlock doesn't work without GUI!";
    }
//	m_controller->powermate()->setBrightness(newValue);
}
