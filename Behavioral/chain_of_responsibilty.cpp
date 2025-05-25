// chain_of_responsibilty.cpp

/*
--- Problem Statement ---
Suppose we have to handle authentication requests with a chain of handlers. 
Depending on the type of authentication request, the appropriate handler in the 
chain handles it, or it is passed along the chain until a handler can process it 
or until the end of the chain is reached.
*/

#include <iostream>
#include <string>
#include <memory>

// Handler Interface
class AuthenticationHandler {
public:
    virtual void setNextHandler(AuthenticationHandler* handler) = 0;
    virtual void handleRequest(const std::string& request) = 0;
    virtual ~AuthenticationHandler() = default;
};

// Concrete Handlers
class UsernamePasswordHandler : public AuthenticationHandler {
private:
    AuthenticationHandler* nextHandler = nullptr;

public:
    void setNextHandler(AuthenticationHandler* handler) override {
        nextHandler = handler;
    }

    void handleRequest(const std::string& request) override {
        if (request == "username_password") {
            std::cout << "Authenticated using username and password." << std::endl;
        } else if (nextHandler) {
            nextHandler->handleRequest(request);
        } else {
            std::cout << "Invalid authentication method." << std::endl;
        }
    }
};

class OAuthHandler : public AuthenticationHandler {
private:
    AuthenticationHandler* nextHandler = nullptr;

public:
    void setNextHandler(AuthenticationHandler* handler) override {
        nextHandler = handler;
    }

    void handleRequest(const std::string& request) override {
        if (request == "oauth_token") {
            std::cout << "Authenticated using OAuth token." << std::endl;
        } else if (nextHandler) {
            nextHandler->handleRequest(request);
        } else {
            std::cout << "Invalid authentication method." << std::endl;
        }
    }
};

void using_smart_pointers() {
    auto oauthHandler = std::make_unique<OAuthHandler>();
    auto usernamePasswordHandler = std::make_unique<UsernamePasswordHandler>();

    // Chain: usernamePasswordHandler -> oauthHandler
    usernamePasswordHandler->setNextHandler(oauthHandler.get());

    // Handling authentication requests
    usernamePasswordHandler->handleRequest("oauth_token");
    usernamePasswordHandler->handleRequest("username_password");
    usernamePasswordHandler->handleRequest("invalid_method");
}

int main() {
    using_smart_pointers();
    return 0;
}