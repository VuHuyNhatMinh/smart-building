from codecs import lookup_error
from rest_framework import generics
from yaml import serialize

from sensors.models import Sensors
from sensors.serializers import SensorSerializer

# TODO: GET, POST method - Dinh Hong Quan

class SensorListCreate(generics.ListCreateAPIView):     #hình như cái này là cả Create và cả GET toàn bộ records về luôn
    queryset = Sensors.objects.all()
    serializer_class = SensorSerializer

    def perform_create(self, serializer):
        serializer.save()
        

class SensorUpdate(generics.UpdateAPIView):
    queryset = Sensors.objects.all()
    serializer_class = SensorSerializer
    lookup_field = 'pk'
    
    def perform_update(self, serializer):
        instance = serializer.save()

class SensorDelete(generics.DestroyAPIView):
    queryset = Sensors.objects.all()
    serializer_class = SensorSerializer
    lookup_field = 'pk'

    def perform_destroy(self, instance):
        instance.delete()
    