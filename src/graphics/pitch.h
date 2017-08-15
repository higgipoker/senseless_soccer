#pragma once

#include <gamelib/graphics/tileset.h>
#include <gamelib/camera/camera.h>

namespace SenselessSoccer {

class PitchTiled : public GameLib::Tileset {
public:
    /**
     * \brief construct
     * \param filename tile image file name
     * \param c camera for deciding what tiles to render
     */
    explicit PitchTiled(const std::string &filename, GameLib::Camera &c);

    /**
     * \brief specialized render function
     * \param window window to render to
     */
    virtual void Render(GameLib::Window &window) override;
private:
};


}// SenselessSoccer
