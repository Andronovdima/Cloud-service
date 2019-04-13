// Copyright 2019 (c) <Cloud9>

#include <gtest/gtest.h>
#include <../include/back.hpp>

TEST(database, good) {
    std::string root = "login";
    Note data = std::any("mail");

    myDataBase.makeNote(root, data);
    Note answer = myDataBase.get(root);

    EXPECT_EQ(std::any_cast<std::string>(answer.GetData()), std::any_cast<std::string>(data.GetData()));
}

TEST(database, bad) {
    std::string root = "login";
    Note data = std::any("mail");

    myDataBase.makeNote(root, data);
    Note answer = myDataBase.get("logout");

    EXPECT_EQ(std::any_cast<std::string>(answer.GetData()), std::string(""));
}

TEST(database, delete_note) {
    std::string root = "login";
    Note data = std::any("mail");

    myDataBase.makeNote(root, data);
    Note answer = myDataBase.get("login");
    EXPECT_EQ(std::any_cast<std::string>(answer.GetData()), std::any_cast<std::string>(data.GetData()));

    myDataBase.deleteNote(root);
    answer = myDataBase.get("login");
    EXPECT_EQ(std::any_cast<std::string>(answer.GetData()), std::string(""));
}

TEST(receiver, execute) {
    Load load("login", "mail");

    myReceiver(&load);

    Note answer = myDataBase.get("login");

    EXPECT_EQ(std::any_cast<std::string>(answer.GetData()), std::string("mail"));
}
