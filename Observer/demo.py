import pickle
import os.path
import base64
import tkinter as tk
from tkinter import messagebox
from email.mime.text import MIMEText
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request

SCOPES = ['https://www.googleapis.com/auth/gmail.send']

def get_credentials():
    """Authenticate using OAuth 2.0 and obtain credentials."""
    creds = None
    if os.path.exists("token.pickle"):
        with open("token.pickle", "rb") as token:
            creds = pickle.load(token)
    
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file("credentials.json", SCOPES)
            creds = flow.run_local_server(port=0)
        
        with open("token.pickle", "wb") as token:
            pickle.dump(creds, token)
    
    return creds

def send_email():
    """Send an email using Gmail API."""
    creds = get_credentials()

    sender_email = entry_sender.get()
    receiver_email = entry_receiver.get()
    company_name = entry_company.get()
    role_id = entry_role.get()
    expertise = entry_expertise.get()

    subject = f"Application for {role_id} – {company_name}"
    body = f"""\
    Dear [Recruiter's Name],

    I hope you're doing well. I am interested in the {role_id} position at {company_name}.  
    My expertise includes {expertise}, and I believe my skills align well with this role.  
    Looking forward to discussing how I can contribute.

    Best regards,  
    {sender_email}
    """

    message = MIMEText(body)
    message['From'] = sender_email
    message['To'] = receiver_email
    message['Subject'] = subject
    raw_message = base64.urlsafe_b64encode(message.as_bytes()).decode()

    try:
        service = creds
        service.send_email(sender_email, receiver_email, raw_message)
        messagebox.showinfo("Success", "Email sent successfully!")
    except Exception as e:
        messagebox.showerror("Error", f"Failed to send email: {e}")

# Create GUI
root = tk.Tk()
root.title("OAuth Email Sender")
root.geometry("400x400")

tk.Label(root, text="Your Email:").pack()
entry_sender = tk.Entry(root, width=40)
entry_sender.pack()

tk.Label(root, text="Recruiter's Email:").pack()
entry_receiver = tk.Entry(root, width=40)
entry_receiver.pack()

tk.Label(root, text="Company Name:").pack()
entry_company = tk.Entry(root, width=40)
entry_company.pack()

tk.Label(root, text="Role ID:").pack()
entry_role = tk.Entry(root, width=40)
entry_role.pack()

tk.Label(root, text="Your Expertise:").pack()
entry_expertise = tk.Entry(root, width=40)
entry_expertise.pack()

tk.Button(root, text="Send Email", command=send_email).pack()

# Run the GUI
root.mainloop()
