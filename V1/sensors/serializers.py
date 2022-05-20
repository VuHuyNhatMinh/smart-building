from rest_framework import serializers
from .models import Sensors

class SensorSerializer(serializers.ModelSerializer):
    class Meta:
        model = Sensors
        fields = ['id', 'mac', 'temp', 'hum']