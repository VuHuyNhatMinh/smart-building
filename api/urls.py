from django.urls import path
from . import views

urlpatterns = [
    # TODO: GET, POST method - Dinh Hong Quan
    path('listCreate/',views.SensorListCreate.as_view()),

    # PUT/PATCH method
    path('update/<int:pk>', views.SensorUpdate.as_view()),

    # DELETE method
    path('delete/<int:pk>', views.SensorDelete.as_view()),
]