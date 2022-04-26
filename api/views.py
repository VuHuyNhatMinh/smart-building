from codecs import lookup_error
from rest_framework import generics
from rest_framework import serializers

from sensors.models import Sensors
from sensors.serializers import SensorSerializer

# TODO: GET, POST method - Dinh Hong Quan

class SensorListCreate(generics.ListCreateAPIView):     #hình như cái này là cả Create và cả GET toàn bộ records về luôn
    queryset = Sensors.objects.all()
    serializer_class = SensorSerializer

    def perform_create(self, serializer):
        serializer.save()

# views to get only one specific record in database
class SensorDetail(generics.RetrieveAPIView):
    queryset = Sensors.objects.all()
    serializer_class = SensorSerializer

#view to create a record in database
class SensorCreate(generics.CreateAPIView):
    qeuryset = Sensors.objects.all()
    serializer_class = SensorSerializer

    def perform_create(self, serializer):
        print(serializer.validated_data)
        mac = serializer.validated_data.get('mac')
        print(mac)
        hum = serializer.validated_data.get('hum')
        print(hum)
        if mac=='':
            mac=hum
            print(mac)
        serializer.save(mac=mac)
        

        

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
    