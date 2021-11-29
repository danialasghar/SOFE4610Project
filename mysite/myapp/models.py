from django.db import models

# Create your models here.
class Conditions(models.Model):
    temperature = models.CharField(max_length=200)
    humidity = models.CharField(max_length=200)
