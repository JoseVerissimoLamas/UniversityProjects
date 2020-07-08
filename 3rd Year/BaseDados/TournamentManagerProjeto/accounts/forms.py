from django import forms
from django.core.validators import RegexValidator
from .models import User, Users


class loginForm(forms.Form):
    username = forms.CharField(label='Username', max_length=50,
                               widget=forms.TextInput(attrs={'placeholder': '', 'class': 'formInput'}))
    password = forms.CharField(widget=forms.PasswordInput(attrs={'placeholder': '', 'class': 'formInput'}))


class registerForm(forms.Form):
    username = forms.CharField(label='Username', max_length=50,
                               widget=forms.TextInput(attrs={'placeholder': '', 'class': 'formInput'}),
                               validators=[RegexValidator(r'^[A-Za-z0-9]+(?:[._-][A-Za-z0-9]+)*$',
                                                          "Username must only contain letters, hyphens, dots, "
                                                          "underscores and numbers. Username can't end with a special "
                                                          "character.", 'Invalid username')])
    password = forms.CharField(widget=forms.PasswordInput(attrs={'placeholder': '', 'class': 'formInput'}))
    confPassword = forms.CharField(label="Confirm Password",
                                   widget=forms.PasswordInput(attrs={'placeholder': '', 'class': 'formInput'}))
    email = forms.EmailField(widget=forms.EmailInput(attrs={'placeholder': '', 'class': 'formInput'}))
    firstName = forms.CharField(label='First Name', max_length=50,
                                widget=forms.TextInput(attrs={'placeholder': '', 'class': 'formInput'}))
    lastName = forms.CharField(label='Last Name', max_length=50,
                               widget=forms.TextInput(attrs={'placeholder': '', 'class': 'formInput'}))
    # added for the accounts_users table info
    contactNumber = forms.IntegerField(label='',
                                       widget=forms.TextInput(attrs={'placeholder': '', 'class': 'formInput'}),
                                       validators=[
                                           RegexValidator(
                                               regex=r'^\+?1?\d{9,15}$',
                                               message='Phone number must be at least 9 digits and maximum 15',
                                               code='invalid_number'),]
                                       )
    # added for the accounts_users table info
    cc = forms.IntegerField(label='Citizen Number',
                            widget=forms.TextInput(attrs={'placeholder': '', 'class': 'formInput'}),
                            validators=[RegexValidator(r'\d{8,8}', 'CC must be 8 digits', 'Invalid CC number')])

    # password validation
    def clean_password2(self):
        password1 = self.cleaned_data.get("password")
        password2 = self.cleaned_data.get("confPassword")
        if password1 and password2 and password1 != password2:
            return False
        return True

    # check if username is already in the database, returns false in case it is not "safe"
    def clean_username2(self):
        username = self.cleaned_data.get("username")
        """ EQUIVALENT SQL """
        # SELECT count(*) FROM 'auth_user' WHERE auth_user.username = username
        if User.objects.filter(username=username).count() != 0:
            return False
        return True

    # check if cc is already in use, returns false in case it is not "safe"
    def clean_cc2(self):
        cc = self.cleaned_data.get("cc")
        """ EQUIVALENT SQL """
        # SELECT count(*) FROM 'accounts_users' WHERE accounts_user.cc = cc
        if Users.objects.filter(cc=cc).count() != 0:
            return False
        return True

    # check if email is already in use, returns false in case it is not "safe"
    def clean_email2(self):
        email = self.cleaned_data.get("email")
        """ EQUIVALENT SQL """
        # SELECT count(*) FROM 'auth_user' WHERE auth_user.email = email
        if User.objects.filter(email=email).count() != 0:
            return False
        return True


class balanceForm(forms.Form):
    # value, label
    CHOICES = [('add', 'Add Money'),
               ('remove', 'Withdraw Money')]

    isAdd = forms.ChoiceField(choices=CHOICES, widget=forms.RadioSelect, required=True)
    balance = forms.IntegerField(label='Balance', max_value=9999)


class editProfile(forms.ModelForm):

    class Meta:
        model = Users
        fields = ['phoneNumber', 'image', 'bio']
