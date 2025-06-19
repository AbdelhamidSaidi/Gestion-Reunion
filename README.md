# **Meeting Management System (GESTION_REUNION) 

This repository contains a **SQL Server database schema** designed for managing meetings, participants, documents, and notifications within an organization. The database, named **GESTION_REUNION**, provides a structured way to handle meeting scheduling, employee invitations, room availability, and follow-up documentation.  
![image](https://github.com/user-attachments/assets/34be5f4b-c5d5-4448-8057-6394ada0ebb0)


## **📌 Features**  

### **1. Meeting Management**  
- Create, modify, and delete meetings (`Reunions` table)  
- Track meeting details (host, room, agenda, duration, type)  
- Check room availability using the `SalleDisponible` function  

### **2. Employee & Role Management**  
- Store employee information (`Employes` table)  
- Define roles (`Roles` table) and associate them with employees  
- Link employees to companies (`Entreprises` table)  

### **3. Invitations & Attendance Tracking**  
- Send and manage meeting invitations (`Invitations` table)  
- Track participant availability (`disponibilite`) and actual attendance (`presence`)  
- Automatically calculate total meeting time per employee (`GetDureeTotaleReunionsEmploye` function)  

### **4. Document & Minutes Management**  
- Upload and link documents to meetings (`Documents` and `Reunions_Documents` tables)  
- Store meeting minutes (`Compte_Rendu` table)  

### **5. Notification System**  
- Send notifications for meeting invitations (`Notifications` and `Notifications_Invitations` tables)  
- Track notification status (sent, received, read, failed)  

### **6. Reporting & Queries**  
- Retrieve meetings by host, room, or type (`GetReunionsParHote`, `GetReunionsParSalle`, `GetReunionsParType`)  
- Generate reports on employee meeting participation (`GenererRapportReunions`)  

## **🛠️ Database Structure**  
The database includes:  
- **Tables**: `Employes`, `Entreprises`, `Roles`, `Salles`, `Reunions`, `Invitations`, `Compte_Rendu`, `Documents`, `Reunions_Documents`, `Notifications`, `Notifications_Invitations`  
- **Stored Procedures**: For CRUD operations, reports, and notifications  
- **User-Defined Functions**: For calculating meeting durations and checking room availability  

## **🚀 Use Cases**  
✔ **Corporate Meeting Scheduling** – Book rooms, invite employees, and track attendance.  
✔ **Document Management** – Attach agendas, reports, and minutes to meetings.  
✔ **Employee Productivity Tracking** – Measure time spent in meetings per employee.  
✔ **Automated Notifications** – Alert participants about upcoming meetings.  


## 🚀 How to Use

1. **Navigate to the project directory** in your terminal:

```bash
cd path/to/your/project
```

2. **Compile the project** using `gcc`:

```bash
gcc -Iincludes src/*.c -o bin/app
```


3. **Run the application**:

```bash
./bin/app
```

Or, compile and run in a single line:

```bash
gcc -Iincludes src/*.c -o bin/app && ./bin/app
```



## 🏆 Auteurs

- Abdelhamid SAIDI - [@abdelhamid_saidi](https://www.linkedin.com/in/abdelhamid-saidi-181582326/)
- Anas RIFAK - [@anas_rifak](https://www.linkedin.com/in/anas-rifak-502347343/)
- Safaa MOUFKI - [@safaa_moufki](https://www.linkedin.com/in/moufki-safaa-6354a0279/)

