// Copyright 2019 (c) <Cloud9>

#pragma once
#include <list>
#include <string>
#include "Commands.hpp"
#include "AbstractClient.hpp"
#include "CreateAccountPermission.hpp"
#include "LoginPermission.hpp"
#include "DownloadPermission.hpp"

permissions_t BasicPermissions() {
    permissions_t permissions = {
        new DownloadPermission /*, new UploadPermission, new MergePermission, new DeleteFilesPermission */
    };
    return  permissions;
}

class ConsoleClient : public AbstractClient {
public:
    ConsoleClient() = default;

    ConsoleClient(permissions_t&& permissions) {
        permissions_ = std::move(permissions);
        for (auto p : permissions_) {
            p->SetOwner(this);
        }
    }

    ConsoleClient(const permissions_t& permissions) {
        permissions_ = permissions;
        for (auto p : permissions_) {
            p->SetOwner(this);
        }
    }

    static ConsoleClient CreateDefault() {
        permissions_t permissions;
        permissions.push_back(new CreateAccountPermission(std::cin, std::cout));
        permissions.push_back(new LoginPermission(std::cin, std::cout));
        return ConsoleClient(std::move(permissions));
    }

    virtual void RunCommand(const std::string& com) {
        
        cmd::CommandParser command;
        if (!command.parse(com)) {
            // help window with commands
            return;
        }

        bool action = false;
        for (auto& p : permissions_) {
            if (p->CanHandle(command.GetCommand())) {
                auto status = p->Handle(command.GetArgs());
                std::cout << status << std::endl;
                action = true;
                break;
            } 
        }

        if (!action) {
            // help window with permissions
            return;
        }
    }

    virtual void SetProfile(const UserData& profile) {
        user_ = profile;
    }

    virtual void ExpandPermissions() {
        auto newps = BasicPermissions();
        permissions_.insert(permissions_.end(), newps.begin(), newps.end());
    }

private:
    UserData user_;
};

// ��������� (�����
// �������
// �������� HTTPS
// 