# Generated by Django 2.2.7 on 2019-11-23 18:02

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('accounts', '0003_auto_20191115_2319'),
    ]

    operations = [
        migrations.RenameField(
            model_name='users',
            old_name='isGestor',
            new_name='hasPriv',
        ),
        migrations.AlterField(
            model_name='users',
            name='phoneNumber',
            field=models.BigIntegerField(),
        ),
        migrations.AlterField(
            model_name='users',
            name='user',
            field=models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, related_name='user_extended', to=settings.AUTH_USER_MODEL),
        ),
    ]