from django.db import models
import uuid

from controllers.models import Controller

class Sensors(models.Model):
    id = models.UUIDField(default=uuid.uuid4, unique=True, primary_key=True, editable=False)
    name = models.CharField(max_length=200, blank=True, null=True)
    macaddress = models.CharField(max_length=200, blank=True, null=True)
    temp = models.FloatField(default=0, blank=True, null=True)
    hum = models.FloatField(default=0, blank=True, null=True)
    controller = models.ForeignKey(Controller, on_delete=models.DO_NOTHING, blank=True, null=True)
    created = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.macaddress