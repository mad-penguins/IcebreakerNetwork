#ifndef ANTARCLICA_RESPONSEUTILS_HPP
#define ANTARCLICA_RESPONSEUTILS_HPP


class ResponseUtils {
public:
    static bool checkObject(const json &val) {
        Response resp(val);
        if (resp.status->code != Code::OK) {
            throw move(APIException(resp.status->code, move(resp.status->str)));
        } else return true;
    }
};

#endif //ANTARCLICA_RESPONSEUTILS_HPP
