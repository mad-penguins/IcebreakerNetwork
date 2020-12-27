#ifndef ANTARCLICA_FILE_HPP
#define ANTARCLICA_FILE_HPP

#include "APIEntity.hpp"
#include "Response.hpp"
#include "Machine.hpp"
#include "Package.hpp"

class File : public APIEntity {
public:
    class FileData : public APIEntity {
    public:
        string name;
        string path;
        string checksum;
        time_t created;
        time_t modified;

        explicit FileData(const json &val) : APIEntity(val) {
            JsonUtils::checkJsonTypes(val, {
                    {"name",     json::value_t::string},
                    {"path",     json::value_t::string},
                    {"checksum", json::value_t::string},
                    {"created",  json::value_t::number_unsigned},
                    {"modified", json::value_t::number_unsigned}
            });

            name = val["name"];
            path = val["path"];
            path = val["checksum"];
            created = val["created"];
            modified = val["modified"];
        }

        void rewrite(vector<char> content) const {
            ofstream ofs(fullName(), ios::binary);
            ofs.write(content.data(), content.size());
            ofs.flush();
            ofs.close();
            content.clear();
        }

        [[nodiscard]] vector<char> read() const {
            ifstream ifs(fullName(), ios::binary | ios::ate);
            ifstream::pos_type pos = ifs.tellg();

            vector<char> result(pos);
            ifs.seekg(0, ios::beg);
            ifs.read(&result[0], pos);

            return move(result);
        }

        [[nodiscard]] inline string fullName() const {
            return path + "/" + name;
        }
    };

    shared_ptr<Machine> machine;
    shared_ptr<FileData> data;
    shared_ptr<Package> package;

    explicit File(const json &val) : APIEntity(val) {
        JsonUtils::checkJsonTypes(val, {
                {"machine", json::value_t::object},
                {"data",    json::value_t::object},
                {"package", json::value_t::object}
        });

        machine = make_shared<Machine>(val["machine"]);
        data = make_shared<FileData>(val["data"]);
        package = make_shared<Package>(val["package"]);
    }

};

#endif //ANTARCLICA_FILE_HPP
