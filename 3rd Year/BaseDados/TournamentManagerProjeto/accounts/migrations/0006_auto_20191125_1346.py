# Generated by Django 2.2.7 on 2019-11-25 13:46

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('accounts', '0005_users_image'),
    ]

    operations = [
        migrations.AlterField(
            model_name='users',
            name='image',
            field=models.ImageField(default='profile-pics/default.png', upload_to='profile-pics'),
        ),
    ]
