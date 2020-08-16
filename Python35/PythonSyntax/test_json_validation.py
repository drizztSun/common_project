from jsonschema import validate
from jsonschema.exceptions import ValidationError, SchemaError
import json

def json_validate(json_data, json_schema):
    """
    :param json_data: Json to be validated
    :param json_schema: schema to be validated against
    :return:
    """
    try:
        validate(json_data, json_schema)
    except ValidationError as val_ex:
        print("Failed to validate json body.  %s" % val_ex.message)
    except SchemaError as ex:
        print("failed to validate json %s against schema %s    message: %s", json_data, json_schema, ex.message)

def certificate_profile():
    """
    :return:
    """
    return {
        "$schema": "https://json-schema.org/schema#",
        "type": "object",
        "properties": {
            "name": {"type": "string", "minLength":1},
            "caId": {"type": "string", "minLength":1},
            "location": {"type": "string", "minLength":1},
            "revocationStatus": {"type": "boolean"},
            "nonExportable": {"type": "boolean"},
            "tpmAttested": {"type": "boolean"},
            "ocspId": {"type": "string"}
        },
        "required": ["name", "caId", "location", "revocationStatus", "nonExportable", "tpmAttested"],
        "additionalProperties": False
    }

if __name__ == '__main__':

    cert_profile = {
        "name": "cert name for test",
        "caId": "ca-01",
        "ocspId": "",
        "location": "system",
        "revocationStatus": True,
        "nonExportable": True,
        "tpmAttested": True
    }

    print(type(json.dumps(cert_profile)))

    print( json_validate(cert_profile, certificate_profile()) )

    if cert_profile["revocationStatus"] and "ocspId" not in cert_profile:
        raise InvalidInputException("OCSP selection missing")