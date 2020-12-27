#ifndef ANTARCLICA_SECTION_HPP
#define ANTARCLICA_SECTION_HPP


#include "entities/Response.hpp"
#include "utils/Utils.hpp"
#include "entities/File.hpp"
#include "entities/User.hpp"

class Wrapper {
    inline static User user;

public:
    static void authorize(const string &login, const string &password);

    template<class TemplateEntity> requires IsEntity<TemplateEntity, APIEntity>
    class Section {
    public:
        static string sectionSlug;

        static shared_ptr<EntityList<TemplateEntity>> getAll(unsigned machine) {
            auto list = Utils::executeNoFormRequest(
                    Utils::NoFormResponse::GET,
                    "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/" + sectionSlug + "s/" +
                    user.accessToken
            ).at("objs");
            return make_shared<EntityList<TemplateEntity>>(list);
        }

        static shared_ptr<TemplateEntity> get(unsigned machine, unsigned id) {
            auto obj = Utils::executeNoFormRequest(
                    Utils::NoFormResponse::GET,
                    "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/" + sectionSlug + "/" +
                    to_string(id) + "/" + user.accessToken
            ).at("obj");
            return move(make_shared<TemplateEntity>(obj));
        }

        static void upload(unsigned machine, const shared_ptr<TemplateEntity> &obj);

        static void update(unsigned machine, const shared_ptr<TemplateEntity> &obj, bool rewrite = true);

        static void remove(unsigned machine, unsigned id) {
            auto obj = Utils::executeNoFormRequest(
                    Utils::NoFormResponse::DELETE,
                    "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/" + sectionSlug + "/" +
                    to_string(id) + "/" + user.accessToken
            );
        }
    };

    class Files : Section<File> {
        static vector<char> getContent(unsigned machine, unsigned id);
    };
};


#endif //ANTARCLICA_SECTION_HPP
