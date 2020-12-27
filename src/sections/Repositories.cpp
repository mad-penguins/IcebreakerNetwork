#include "sections/Section.hpp"

template<> string Wrapper::Section<Repository>::sectionSlug = "repo";

template<>
void Wrapper::Section<Repository>::upload(unsigned machine, const shared_ptr<Repository> &obj) {
    json response = Utils::executeFormRequest(
            Utils::FormResponse::POST,
            "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/" + sectionSlug + "s/" +
            user.accessToken,
            cpr::Multipart{
                    {"name",       obj->data->name},
                    {"url",        obj->data->URL},
                    {"manager",    obj->data->manager},
                    {"machine_id", obj->machine->id}
            }
    );
    ResponseUtils::checkObject(response);
    assert(response.is_object());
}

template<>
void Wrapper::Section<Repository>::update(unsigned machine, const shared_ptr<Repository> &obj, bool rewrite) {
    auto response = Utils::executeFormRequest(
            Utils::FormResponse::PUT,
            "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/" + sectionSlug + "/" +
            to_string(obj->id) + "/" + (rewrite ? "rew" : "clone") + "/" + user.accessToken,
            cpr::Multipart{
                    {"name",       obj->data->name},
                    {"url",        obj->data->URL},
                    {"manager",    obj->data->manager},
                    {"machine_id", obj->machine->id}
            }
    );
    assert(response.is_object());
}

template
class Wrapper::Section<Repository>;
