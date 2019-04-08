// Copyright 2019 (c) <Cloud9>

#include <gtest/gtest.h>
#include <client_side.hpp>

TEST(�lient, CheckLogin) {
  ConsoleClient& client = ConsoleClient::getInstance();
  ConsoleClientDestroyer destructor;
  destructor.initialize(&client);

  std::string login = "Admin";
  std::string password = "Admin";
  EXPECT_TRUE(client.login(login, password));

  login = "Admin";
  password = "WrongPassword";
  EXPECT_FALSE(client.login(login, password));
}

TEST(�lient, CheckRun) {
  auto resolver = new BasicResolver();
  ConsoleClient& client = ConsoleClient::getInstance();
  ConsoleClientDestroyer destructor;
  destructor.initialize(&client);

  EXPECT_THROW(client.run("cloud merge"), std::runtime_error);

  client.set_resolver(resolver);
  EXPECT_NO_THROW(client.run("cloud merge"));
}

TEST(REST, Requests) {
  auto client_server = new BoostHTTPClient;
  EXPECT_NO_THROW(client_server->handle_request("GET file.txt"));
  EXPECT_NO_THROW(client_server->handle_request("POST file.txt"));
  EXPECT_NO_THROW(client_server->handle_request("DELETE file.txt"));
  EXPECT_NO_THROW(client_server->handle_request("PUT file.txt"));

  EXPECT_EQ(client_server->handle_request("GET file.txt"), "success...");
  EXPECT_EQ(client_server->handle_request("POST file.txt"), "success...");
  EXPECT_EQ(client_server->handle_request("DELETE file.txt"), "success...");
  EXPECT_EQ(client_server->handle_request("PUT file.txt"), "success...");
}
