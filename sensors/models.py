from django.db import models

class Sensors(models.Model):
    mac = models.CharField(max_length=50, blank=True, null=True)
    temp = models.FloatField(default=0, blank=True, null=True)
    hum = models.FloatField(default=0, blank=True, null=True)
