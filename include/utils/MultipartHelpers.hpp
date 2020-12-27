#ifndef ANTARCLICA_MULTIPARTHELPERS_HPP
#define ANTARCLICA_MULTIPARTHELPERS_HPP


#include <cpr/cpr.h>
#include "entities/File.hpp"

using namespace std;

class MultipartHelpers {
public:
    static cpr::Multipart generateFormFile(const shared_ptr<File> &file) {
        return move(cpr::Multipart{
                {"path",           file->data->path},
                {"checksum",       file->data->checksum},
                {"created",        file->data->created},
                {"modified",       file->data->modified},
                {"package_id",     file->package->id},
                {"machine_id",     file->machine->id},
                {file->data->name, cpr::File{file->data->fullName()}},
        });
    }
};

#endif //ANTARCLICA_MULTIPARTHELPERS_HPP
