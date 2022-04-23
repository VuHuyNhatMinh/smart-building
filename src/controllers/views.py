from django.shortcuts import render
from .models import Controller

def controllers(request):
    controllers = Controller.objects.all()
    context = {
        'controllers': controllers,
    }
    return render(request, 'controllers/controllers.html', context)