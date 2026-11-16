#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace geode::prelude;

// Edit these timestamps (seconds from the start of the level) for your route.
// Example: { 3.25f, true } means CLICK at 3.25 seconds.
//           { 3.60f, false } means RELEASE at 3.60 seconds.
struct Cue {
    float time;
    bool click;
};

static const std::vector<Cue> CUES = {
    { 3.25f, true  },
    { 3.60f, false },
    { 5.10f, true  },
    { 5.42f, false },
    { 7.00f, true  },
    { 7.28f, false }
};

class $modify(CueTrainerPlayLayer, PlayLayer) {
    struct Fields {
        float elapsed = 0.f;
        CCLabelBMFont* hud = nullptr;
        size_t nextCue = 0;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        m_fields->elapsed = 0.f;
        m_fields->nextCue = 0;

        auto label = CCLabelBMFont::create("CUE TRAINER: READY", "bigFont.fnt");
        if (label) {
            auto win = CCDirector::sharedDirector()->getWinSize();
            label->setAnchorPoint({0.f, 1.f});
            label->setScale(0.38f);
            label->setPosition({12.f, win.height - 12.f});
            label->setZOrder(9999);
            this->addChild(label);
            m_fields->hud = label;
        }
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);
        if (!m_fields->hud)
            return;

        m_fields->elapsed += dt;

        while (m_fields->nextCue < CUES.size() &&
               CUES[m_fields->nextCue].time < m_fields->elapsed - 0.18f) {
            ++m_fields->nextCue;
        }

        if (m_fields->nextCue >= CUES.size()) {
            m_fields->hud->setString("CUE TRAINER: FINISHED");
            return;
        }

        auto const& cue = CUES[m_fields->nextCue];
        float remaining = cue.time - m_fields->elapsed;

        std::ostringstream out;
        if (std::fabs(remaining) <= 0.18f) {
            out << (cue.click ? "CLICK NOW" : "RELEASE NOW");
        } else {
            out << (cue.click ? "NEXT: CLICK  " : "NEXT: RELEASE  ")
                << std::fixed << std::setprecision(2)
                << remaining << "s";
        }
        m_fields->hud->setString(out.str().c_str());
    }
};
