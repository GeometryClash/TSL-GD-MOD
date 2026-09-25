#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelCell.hpp>

using namespace geode::prelude;

class $modify(TslLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;

		auto difficultyLabel = CCLabelBMFont::create("TSL: #313", "bigFont.fnt");

		if (!difficultyLabel) return true;

		difficultyLabel->setScale(0.35f);
		difficultyLabel->setAnchorPoint({0.5f, 1.f});

		auto difficulty = this->m_difficultySprite;

		if (!difficulty) return true;

		auto pos = difficulty->getPosition();

		difficultyLabel->setPosition(
			pos.x,
			pos.y - difficulty->getContentSize().height / 2.f - 6.f
		);

		this->addChild(difficultyLabel, 1000);

		return true;
	}
};

class $modify(TslLevelCell, LevelCell) {
	void loadFromLevel(GJGameLevel* level) {
		LevelCell::loadFromLevel(level);

		auto testLabel = CCLabelBMFont::create("TSL: #313", "bigFont.fnt");

		if (!testLabel) return;

		testLabel->setScale(0.3f);
		testLabel->setAnchorPoint({0.f, 0.5f});

		testLabel->setPosition(
			290.f,
			14.f
		);

		this->addChild(testLabel, 1000);
	}
};