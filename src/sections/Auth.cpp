#include <sections/Section.hpp>

void Wrapper::authorize(const string &login, const string &password) {
    auto val = Utils::executeFormRequest(Utils::FormResponse::POST, "login", cpr::Multipart{
            {"login",    login},
            {"password", password}
    }).at("obj");
    user = move(User(val));
}
