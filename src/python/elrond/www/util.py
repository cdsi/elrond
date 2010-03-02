from django.core import serializers
from django.http import HttpResponse

class JsonResponse(HttpResponse):
        content_type = 'application/json'

class JsonResponse200(JsonResponse):
        status = 200

class JsonResponse201(JsonResponse):
        status = 201

class JsonResponse204(JsonResponse):
        status = 204

class JsonResponse404(JsonResponse):
        status = 404

class JsonResponse500(JsonResponse):
        status = 500

def to_json(data):
        return serializers.serialize('json', data, indent=8)

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
