from django.shortcuts import render
from .models import Sensors

def sensors(request):
    sensors = Sensors.objects.order_by('-created')[:2]
    print(sensors)
    context = {
        'sensors': sensors,
    }
    return render(request, 'sensors/sensors.html', context)