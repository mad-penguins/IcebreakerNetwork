#include "sections/Section.hpp"

template<> string Wrapper::Section<Package>::sectionSlug = "pkg";

template<>
void Wrapper::Section<Package>::upload(unsigned machine, const shared_ptr<Package> &obj) {
    auto response = Utils::executeFormRequest(
            Utils::FormResponse::POST,
            "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/" + sectionSlug + "s/" +
            user.accessToken,
            cpr::Multipart{
                    {"name",       obj->data->name},
                    {"repo_id",    obj->repository->id},
                    {"machine_id", obj->machine->id}
            }
    );
    assert(response.is_object());
}

template<>
void Wrapper::Section<Package>::update(unsigned int machine, const shared_ptr<Package> &obj, bool rewrite) {
    auto response = Utils::executeFormRequest(
            Utils::FormResponse::PUT,
            "/user/" + to_string(user.id) + "/machine/" + to_string(machine) + "/" + sectionSlug + "/" +
            to_string(obj->id) + "/" + (rewrite ? "rew" : "clone") + "/" + user.accessToken,
            cpr::Multipart{
                    {"name",       obj->data->name},
                    {"repo_id",    obj->repository->id},
                    {"machine_id", obj->machine->id}
            }
    );
    assert(response.is_object());
}

template
class Wrapper::Section<Package>;
