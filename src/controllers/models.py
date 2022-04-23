from django.db import models
from users.models import Profile
import uuid

class Controller(models.Model):
    id = models.UUIDField(default=uuid.uuid4, unique=True, primary_key=True, editable=False)
    name = models.CharField(max_length=200, blank=True, null=True)
    macAddress = models.CharField(max_length=200, blank=True, null=True)
    owner = models.ForeignKey(Profile, on_delete=models.DO_NOTHING,null=True, blank=True)
    created = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.macAddress