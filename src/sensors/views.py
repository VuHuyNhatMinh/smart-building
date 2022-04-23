from django.shortcuts import render
from .models import Sensors
import json
# Create your views here.
from django.http import JsonResponse
from django.forms.models import model_to_dict
from rest_framework.response import Response
from rest_framework.decorators import api_view

# def sensors(request):
#     sensors = Sensors.objects.order_by('-created')[:2]
#     print(sensors)
#     context = {
#         'sensors': sensors,
#     }
#     return render(request, 'sensors/sensors.html', context)


@api_view(["GET"])
def sensors(request, *args, **kwargs):
    """
    Bây giờ cái api_home này là một django rest framework api 
    """
    sensors = Sensors.objects.order_by('-created').first()
    print(sensors)
    data = {}
    if sensors:
        # data["id"] = model_data.id
        # data["title"] = model_data.title
        # data["content"] = model_data.content
        # data["price"] = model_data.price
        data = model_to_dict(sensors, fields=['id', 'macaddress', 'temp', 'hum'])   #dòng này bằng tất cả các dòng trên
    return Response(data)