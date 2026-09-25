#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/utils/web.hpp>
#include <unordered_map>

using namespace geode::prelude;

static std::unordered_map<int, int> tsl;

static void loadTSL() {
    auto r = web::WebRequest().getSync(
        "https://tslbackend-v2.shittylist.workers.dev/api/ordered-levels?list_id=main"
    );

    if (!r.ok())
        return;

    auto data = r.json();

    if (!data)
        return;

    for (auto& e : data.unwrap()) {
        auto id = e["content"]["id"].asInt();
        auto pos = e["position"].asInt();

        if (id && pos)
            tsl[(int)id.unwrap()] = (int)pos.unwrap();
    }
}

class $modify(TslLevelInfo, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge))
            return false;

        if (!tsl.contains(level->m_levelID))
            return true;

        auto difficulty = this->m_difficultySprite;

        if (!difficulty)
            return true;

        auto label = CCLabelBMFont::create(
            fmt::format("TSL: #{}", tsl[level->m_levelID]).c_str(),
            "bigFont.fnt"
        );

        if (!label)
            return true;

        auto pos = difficulty->getPosition();

        label->setScale(0.35f);
        label->setAnchorPoint({0.5f, 1.f});
        label->setPosition(
            pos.x,
            pos.y - difficulty->getContentSize().height / 2.f
            - (level->m_coins > 0 ? 14.f : 6.f)
        );

        this->addChild(label, 1000);

        return true;
    }
};

class $modify(TslLevelCell, LevelCell) {
    void loadFromLevel(GJGameLevel* level) {
        LevelCell::loadFromLevel(level);

        if (!tsl.contains(level->m_levelID))
            return;

        auto label = CCLabelBMFont::create(
            fmt::format("TSL: #{}", tsl[level->m_levelID]).c_str(),
            "bigFont.fnt"
        );

        if (!label)
            return;

        label->setScale(0.3f);
        label->setAnchorPoint({0.f, 0.5f});
        label->setPosition(290.f, 14.f);

        this->addChild(label, 1000);
    }
};

$on_mod(Loaded) {
    loadTSL();
}