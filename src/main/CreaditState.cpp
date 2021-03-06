#include "CreaditState.h"
#include "MenuState.h"

#include <Core/Root.hpp>
#include <Scene/StateManager.hpp>
#include <Core/ResourceManager.hpp>
#include <Graphics/CameraComponent.hpp>
#include <Gui/GuiManager.hpp>

void CreaditState::onInitialize() {
    auto scene = addScene(new dt::Scene("creadit_state_scene"));

    dt::ResourceManager::get()->addDataPath(QDir("data"));
    dt::ResourceManager::get()->addResourceLocation("gui", "FileSystem");
    dt::ResourceManager::get()->addResourceLocation("images","FileSystem", true);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    auto camnode = scene->addChildNode(new dt::Node("camera_node"));
    camnode->setPosition(Ogre::Vector3(0, 5, 10));
    camnode->addComponent(new dt::CameraComponent("cam"))->lookAt(Ogre::Vector3(0, 0, 0));

    // GUI
    dt::GuiRootWindow& win = dt::GuiManager::get()->getRootWindow();

    auto background_imagebox = win.addChildWidget(new dt::GuiImageBox("credit_background_imagebox"));
    background_imagebox->setPosition(0,0);
    background_imagebox->setSize(1.0f,1.0f);
    background_imagebox->setImageTexture("Space.png");

    auto coordination = win.getMyGUIWidget()->getAbsoluteCoord();       //窗口分辨率
    int size_h = (float)coordination.width / 10.0f;
    int size_v = (float)coordination.height / 10.0f;

    auto logo = win.addChildWidget(new dt::GuiImageBox("credit_logo")).get();
    logo->setImageTexture("logo.png");
    logo->setPosition(coordination.width / 15, coordination.height / 13);
    logo->setSize(0.5f, 0.15f); 

    auto creadit = win.addChildWidget(new dt::GuiImageBox("logo")).get();
    creadit->setImageTexture("creadit.png");
    creadit->setPosition(coordination.width / 15, coordination.height * 0.6);
    creadit->setSize(0.3f, 0.3f); 

    auto cancel_button = win.addChildWidget(new dt::GuiButton("credit_cancel_button"));
    cancel_button->setCaption(QString::fromLocal8Bit("返回主菜单"));
    cancel_button->setSize(size_h, size_v * 0.5);
    cancel_button->setPosition(size_h * 8, size_v * 9);
    cancel_button->getMyGUIWidget()->eventMouseButtonClick += MyGUI::newDelegate(this, &CreaditState::onClick);
}

void CreaditState::onClick(MyGUI::Widget* sender) {
    if (sender->getName() == "Gui.credit_cancel_button") {
        dt::StateManager::get()->pop();
        dt::StateManager::get()->setNewState(new MenuState());
    }
}

void CreaditState::updateStateFrame(double simulation_frame_time) {
}