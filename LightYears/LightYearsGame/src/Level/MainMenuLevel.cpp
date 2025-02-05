#include"Level/MainMenuLevel.h"
#include"widgets/MainMenuHUD.h"

namespace ly
{
    MainMenuLevel::MainMenuLevel(Application *owningApp)
        :World{owningApp}
    {
        mMainMenuHUD = SpawnHUD<MainMenuHUD>();
    }

    void MainMenuLevel::BeginPlay()
    {
        mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
        mMainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);        
    }

    void MainMenuLevel::StartGame()
    {
        LOG("Starting Game");
    }

    void MainMenuLevel::QuitGame()
    {
        LOG("Quiting Game");
    }
}