#include <gtest/gtest.h>
#include "include/BattleSystem.h"
#include "include/NPCFactory.h"
#include "include/ConsoleLogger.h"
#include "include/FileLogger.h"

// тест создания нпц
TEST(NPCFactoryTest, CreateNPCTest) {
    auto trader = NPCFactory::createNPC("SlaveTrader", "Trader1", 100, 100);
    auto knight = NPCFactory::createNPC("Knight", "Knight1", 200, 200);
    auto squirrel = NPCFactory::createNPC("Squirrel", "Squirrel1", 150, 150);

    EXPECT_EQ(trader->getType(), "SlaveTrader");
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(squirrel->getType(), "Squirrel");

    EXPECT_EQ(trader->getX(), 100);
    EXPECT_EQ(knight->getY(), 200);
    EXPECT_EQ(squirrel->getName(), "Squirrel1");
}

// Тест на взаимодействие с NPC
TEST(NPCTest, CanKillTest) {
    auto trader = NPCFactory::createNPC("SlaveTrader", "Trader1", 100, 100);
    auto knight = NPCFactory::createNPC("Knight", "Knight1", 200, 200);
    auto squirrel = NPCFactory::createNPC("Squirrel", "Squirrel1", 150, 150);

    EXPECT_TRUE(knight->canKill(*trader));
    EXPECT_FALSE(trader->canKill(*knight));
    EXPECT_TRUE(trader->canKill(*squirrel));
    EXPECT_FALSE(squirrel->canKill(*knight));
}

// Тест для BattleSystem
TEST(BattleSystemTest, BattleTest) {
    BattleSystem battleSystem;
    battleSystem.addObserver(std::make_unique<ConsoleLogger>());

    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(NPCFactory::createNPC("SlaveTrader", "Trader1", 100, 100));
    npcs.push_back(NPCFactory::createNPC("Knight", "Knight1", 105, 105));
    npcs.push_back(NPCFactory::createNPC("Squirrel", "Squirrel1", 150, 150));

    battleSystem.battle(npcs, 10);

    EXPECT_EQ(npcs.size(), 2);
    EXPECT_EQ(npcs[0]->getType(), "Knight");
    EXPECT_EQ(npcs[1]->getType(), "Squirrel");
}

// Тест на уведомления наблюдателей
TEST(ObserverTest, ConsoleLoggerTest) {
    ConsoleLogger logger;
    auto trader = NPCFactory::createNPC("SlaveTrader", "Trader1", 100, 100);
    auto knight = NPCFactory::createNPC("Knight", "Knight1", 200, 200);

    testing::internal::CaptureStdout();
    logger.onKill(*knight, *trader);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Knight (Knight1) killed SlaveTrader (Trader1)\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
