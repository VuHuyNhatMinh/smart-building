from django.urls import path
from . import views

urlpatterns = [
    # TODO: GET, POST method - Dinh Hong Quan
    path('listCreate1/',views.SensorListCreate1.as_view()),

    path('listCreate2/',views.SensorListCreate2.as_view()),

    #retrieve only one specific record in database
    path('retrieve/<int:pk>/',views.SensorDetail.as_view()),

    #create one record in database
    path('create/',views.SensorCreate.as_view()),

    # PUT/PATCH method
    path('update/<int:pk>/', views.SensorUpdate.as_view()),

    # DELETE method
    path('delete/<int:pk>/', views.SensorDelete.as_view()),
]