from django.db import models
from django.utils import timezone
import datetime
# Create your models here.


class Coordinator(models.Model):

    def __str__(self):
        return self.full_name

    full_name = models.CharField(max_length=80)
    email = models.CharField(max_length=120)


class Event(models.Model):

    def __str__(self):
        return self.name

    coordinator = models.ForeignKey(Coordinator, on_delete=models.CASCADE)
    name = models.CharField(max_length=300)
    start = models.DateTimeField()
    end = models.DateTimeField()


class Team(models.Model):

    def __str__(self):
        return self.name

    event = models.ForeignKey(Event, on_delete=models.CASCADE)
    name = models.CharField(max_length=80)


class Member(models.Model):

    def __str__(self):
        return self.name

    team = models.ForeignKey(Team, on_delete=models.CASCADE)
    name = models.CharField(max_length=80)
    captain = models.BooleanField()


class Device(models.Model):

    def __str__(self):
        return self.serial

    team = models.ForeignKey(Team, on_delete=models.CASCADE)
    serial = models.BigIntegerField()
    is_speed = models.BooleanField()


class Ping(models.Model):

    def __str__(self):
        return self.count

    device = models.ForeignKey(Device, on_delete=models.CASCADE)
    count = models.PositiveSmallIntegerField()
    time = models.DateTimeField(default=timezone.now)
