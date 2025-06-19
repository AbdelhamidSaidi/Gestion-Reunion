USE [master]
GO
/****** Object:  Database [GESTION_REUNION]    Script Date: 3/24/2025 11:48:12 AM ******/
CREATE DATABASE [GESTION_REUNION]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'GESTION_REUNION', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL12.MSSQLSERVER\MSSQL\DATA\GESTION_REUNION.mdf' , SIZE = 4288KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'GESTION_REUNION_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL12.MSSQLSERVER\MSSQL\DATA\GESTION_REUNION_log.ldf' , SIZE = 1072KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [GESTION_REUNION] SET COMPATIBILITY_LEVEL = 120
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [GESTION_REUNION].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [GESTION_REUNION] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET ARITHABORT OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [GESTION_REUNION] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [GESTION_REUNION] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET  ENABLE_BROKER 
GO
ALTER DATABASE [GESTION_REUNION] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [GESTION_REUNION] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET RECOVERY FULL 
GO
ALTER DATABASE [GESTION_REUNION] SET  MULTI_USER 
GO
ALTER DATABASE [GESTION_REUNION] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [GESTION_REUNION] SET DB_CHAINING OFF 
GO
ALTER DATABASE [GESTION_REUNION] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [GESTION_REUNION] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
ALTER DATABASE [GESTION_REUNION] SET DELAYED_DURABILITY = DISABLED 
GO
EXEC sys.sp_db_vardecimal_storage_format N'GESTION_REUNION', N'ON'
GO
USE [GESTION_REUNION]
GO
/****** Object:  UserDefinedFunction [dbo].[GetDureeTotaleReunionsEmploye]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[GetDureeTotaleReunionsEmploye](@id_employe INT)
RETURNS INT
AS
BEGIN
    DECLARE @duree_totale INT;
    SELECT @duree_totale = SUM(duree)
    FROM Reunions R
    INNER JOIN Invitations I ON R.id_reunion = I.id_reunion
    WHERE I.id_employe = @id_employe;
    RETURN ISNULL(@duree_totale, 0);
END;
GO
/****** Object:  UserDefinedFunction [dbo].[SalleDisponible]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[SalleDisponible](@id_salle INT, @date_debut DATETIME, @duree INT)
RETURNS BIT
AS
BEGIN
    DECLARE @date_fin DATETIME = DATEADD(MINUTE, @duree, @date_debut);
    IF EXISTS (
        SELECT 1
        FROM Reunions
        WHERE id_salle = @id_salle
          AND ((date_debut BETWEEN @date_debut AND @date_fin)
          OR (DATEADD(MINUTE, duree, date_debut) BETWEEN @date_debut AND @date_fin))
			   )
    BEGIN
        RETURN 0; -- Salle non disponible
    END
    RETURN 1; -- Salle disponible
END;
GO
/****** Object:  Table [dbo].[Compte_Rendu]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Compte_Rendu](
	[id_compte_rendu] [int] IDENTITY(1,1) NOT NULL,
	[id_auteur] [int] NOT NULL,
	[id_reunion] [int] NOT NULL,
	[contenu] [nvarchar](1000) NOT NULL,
	[date_redaction] [datetime] NOT NULL DEFAULT (getdate()),
PRIMARY KEY CLUSTERED 
(
	[id_compte_rendu] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Documents]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Documents](
	[id_document] [int] IDENTITY(1,1) NOT NULL,
	[nom] [nvarchar](255) NOT NULL,
	[lien_document] [nvarchar](255) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_document] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Employes]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Employes](
	[id_employe] [int] IDENTITY(1,1) NOT NULL,
	[id_entreprise] [int] NULL,
	[cin] [nvarchar](20) NOT NULL,
	[nom] [nvarchar](50) NOT NULL,
	[prenom] [nvarchar](50) NOT NULL,
	[email] [nvarchar](255) NOT NULL,
	[phone] [nvarchar](50) NOT NULL,
	[id_role] [int] NULL,
 CONSTRAINT [PK__Employes__420CFD16CB2338C7] PRIMARY KEY CLUSTERED 
(
	[id_employe] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
 CONSTRAINT [UQ__Employes__AB6E6164A9C4DA05] UNIQUE NONCLUSTERED 
(
	[email] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
 CONSTRAINT [UQ__Employes__D837D0244300AF1B] UNIQUE NONCLUSTERED 
(
	[cin] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Entreprises]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Entreprises](
	[id_entreprise] [int] IDENTITY(1,1) NOT NULL,
	[nom_entreprise] [nvarchar](200) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_entreprise] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Invitations]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Invitations](
	[id_employe] [int] NOT NULL,
	[id_reunion] [int] NOT NULL,
	[disponibilite] [varchar](20) NOT NULL,
	[presence] [varchar](20) NOT NULL,
	[type_participation] [varchar](20) NOT NULL,
 CONSTRAINT [PK__Invitati__672343DEC957AA55] PRIMARY KEY CLUSTERED 
(
	[id_employe] ASC,
	[id_reunion] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Notifications]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Notifications](
	[id_notification] [int] IDENTITY(1,1) NOT NULL,
	[type_notification] [varchar](100) NOT NULL,
	[message] [nvarchar](1000) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_notification] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Notifications_Invitations]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Notifications_Invitations](
	[id_employe] [int] NOT NULL,
	[id_reunion] [int] NOT NULL,
	[id_notification] [int] NOT NULL,
	[date_envoi] [datetime] NOT NULL CONSTRAINT [DF__Notificat__date___0C85DE4D]  DEFAULT (getdate()),
	[status] [nvarchar](20) NOT NULL,
 CONSTRAINT [PK__Notifica__49B11F5A3ACD56D2] PRIMARY KEY CLUSTERED 
(
	[id_employe] ASC,
	[id_reunion] ASC,
	[id_notification] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Reunions]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Reunions](
	[id_reunion] [int] IDENTITY(1,1) NOT NULL,
	[id_hote] [int] NOT NULL,
	[id_salle] [int] NULL,
	[ordre_jour] [nvarchar](1000) NOT NULL,
	[date_debut] [datetime] NOT NULL,
	[duree] [int] NOT NULL,
	[lien] [nvarchar](255) NULL,
	[type_reunion] [nvarchar](100) NOT NULL,
 CONSTRAINT [PK__Reunions__52FBEC8329DC6ABF] PRIMARY KEY CLUSTERED 
(
	[id_reunion] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Reunions_Documents]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Reunions_Documents](
	[id_document] [int] NOT NULL,
	[id_reunion] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_document] ASC,
	[id_reunion] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Roles]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Roles](
	[id_role] [int] IDENTITY(1,1) NOT NULL,
	[nom_role] [varchar](50) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_role] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
UNIQUE NONCLUSTERED 
(
	[nom_role] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Salles]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Salles](
	[id_salle] [int] IDENTITY(1,1) NOT NULL,
	[nom] [nvarchar](255) NOT NULL,
	[capacite] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_salle] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
ALTER TABLE [dbo].[Compte_Rendu]  WITH CHECK ADD FOREIGN KEY([id_auteur])
REFERENCES [dbo].[Employes] ([id_employe])
GO
ALTER TABLE [dbo].[Compte_Rendu]  WITH CHECK ADD  CONSTRAINT [FK__Compte_Re__id_re__6754599E] FOREIGN KEY([id_reunion])
REFERENCES [dbo].[Reunions] ([id_reunion])
GO
ALTER TABLE [dbo].[Compte_Rendu] CHECK CONSTRAINT [FK__Compte_Re__id_re__6754599E]
GO
ALTER TABLE [dbo].[Employes]  WITH CHECK ADD FOREIGN KEY([id_role])
REFERENCES [dbo].[Roles] ([id_role])
GO
ALTER TABLE [dbo].[Employes]  WITH CHECK ADD  CONSTRAINT [FK_Employes_Entreprises] FOREIGN KEY([id_entreprise])
REFERENCES [dbo].[Entreprises] ([id_entreprise])
GO
ALTER TABLE [dbo].[Employes] CHECK CONSTRAINT [FK_Employes_Entreprises]
GO
ALTER TABLE [dbo].[Invitations]  WITH CHECK ADD  CONSTRAINT [FK__Invitatio__id_em__48CFD27E] FOREIGN KEY([id_employe])
REFERENCES [dbo].[Employes] ([id_employe])
GO
ALTER TABLE [dbo].[Invitations] CHECK CONSTRAINT [FK__Invitatio__id_em__48CFD27E]
GO
ALTER TABLE [dbo].[Invitations]  WITH CHECK ADD  CONSTRAINT [FK__Invitatio__id_re__49C3F6B7] FOREIGN KEY([id_reunion])
REFERENCES [dbo].[Reunions] ([id_reunion])
GO
ALTER TABLE [dbo].[Invitations] CHECK CONSTRAINT [FK__Invitatio__id_re__49C3F6B7]
GO
ALTER TABLE [dbo].[Notifications_Invitations]  WITH CHECK ADD  CONSTRAINT [FK__Notificat__id_em__0E6E26BF] FOREIGN KEY([id_employe])
REFERENCES [dbo].[Employes] ([id_employe])
GO
ALTER TABLE [dbo].[Notifications_Invitations] CHECK CONSTRAINT [FK__Notificat__id_em__0E6E26BF]
GO
ALTER TABLE [dbo].[Notifications_Invitations]  WITH CHECK ADD  CONSTRAINT [FK__Notificat__id_no__10566F31] FOREIGN KEY([id_notification])
REFERENCES [dbo].[Notifications] ([id_notification])
GO
ALTER TABLE [dbo].[Notifications_Invitations] CHECK CONSTRAINT [FK__Notificat__id_no__10566F31]
GO
ALTER TABLE [dbo].[Notifications_Invitations]  WITH CHECK ADD  CONSTRAINT [FK__Notificat__id_re__0F624AF8] FOREIGN KEY([id_reunion])
REFERENCES [dbo].[Reunions] ([id_reunion])
GO
ALTER TABLE [dbo].[Notifications_Invitations] CHECK CONSTRAINT [FK__Notificat__id_re__0F624AF8]
GO
ALTER TABLE [dbo].[Reunions]  WITH CHECK ADD  CONSTRAINT [FK__Reunions__id_hot__38996AB5] FOREIGN KEY([id_hote])
REFERENCES [dbo].[Employes] ([id_employe])
GO
ALTER TABLE [dbo].[Reunions] CHECK CONSTRAINT [FK__Reunions__id_hot__38996AB5]
GO
ALTER TABLE [dbo].[Reunions]  WITH CHECK ADD  CONSTRAINT [FK__Reunions__id_sal__37A5467C] FOREIGN KEY([id_salle])
REFERENCES [dbo].[Salles] ([id_salle])
GO
ALTER TABLE [dbo].[Reunions] CHECK CONSTRAINT [FK__Reunions__id_sal__37A5467C]
GO
ALTER TABLE [dbo].[Reunions_Documents]  WITH CHECK ADD FOREIGN KEY([id_document])
REFERENCES [dbo].[Documents] ([id_document])
GO
ALTER TABLE [dbo].[Reunions_Documents]  WITH CHECK ADD  CONSTRAINT [FK__Reunions___id_re__6EF57B66] FOREIGN KEY([id_reunion])
REFERENCES [dbo].[Reunions] ([id_reunion])
GO
ALTER TABLE [dbo].[Reunions_Documents] CHECK CONSTRAINT [FK__Reunions___id_re__6EF57B66]
GO
ALTER TABLE [dbo].[Notifications_Invitations]  WITH CHECK ADD  CONSTRAINT [CK__Notificat__statu__0D7A0286] CHECK  (([status]='Echec' OR [status]='Lu' OR [status]='Recu' OR [status]='Envoye'))
GO
ALTER TABLE [dbo].[Notifications_Invitations] CHECK CONSTRAINT [CK__Notificat__statu__0D7A0286]
GO
/****** Object:  StoredProcedure [dbo].[AjouterCompteRendu]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AjouterCompteRendu]
    @id_auteur INT,
    @id_reunion INT,
    @contenu NVARCHAR(1000),
    @date_redaction DATETIME
AS
BEGIN
    INSERT INTO Compte_Rendu (id_auteur, id_reunion, contenu, date_redaction)
    VALUES (@id_auteur, @id_reunion, @contenu, @date_redaction);
END;
GO
/****** Object:  StoredProcedure [dbo].[AjouterDocumentReunion]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AjouterDocumentReunion]
    @id_reunion INT,
    @nom VARCHAR(255),
    @lien_document VARCHAR(255)
AS
BEGIN
    DECLARE @id_document INT;

    INSERT INTO Documents (nom, lien_document)
    VALUES (@nom, @lien_document);

    SET @id_document = SCOPE_IDENTITY();

    INSERT INTO Reunions_Documents (id_document, id_reunion)
    VALUES (@id_document, @id_reunion);
END;
GO
/****** Object:  StoredProcedure [dbo].[AjouterEmploye]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AjouterEmploye]
    @id_entreprise INT,
    @cin VARCHAR(20),
    @nom VARCHAR(50),
    @prenom VARCHAR(50),
    @email VARCHAR(100),
    @phone VARCHAR(20),
    @id_role INT
AS
BEGIN

    IF NOT EXISTS (SELECT 1 FROM Entreprises WHERE id_entreprise = @id_entreprise)
    BEGIN
        RAISERROR('Enterprise does not exist.', 16, 1);
        RETURN;
    END

	 IF EXISTS (SELECT 1 FROM Employes WHERE cin = @cin)
    BEGIN
        RAISERROR('Employee with this CIN already exists.', 16, 1);
        RETURN;
    END

    INSERT INTO Employes (id_entreprise, cin, nom, prenom, email, phone, id_role)
    VALUES (@id_entreprise, @cin, @nom, @prenom, @email, @phone, @id_role);
END;
GO
/****** Object:  StoredProcedure [dbo].[AjouterNotification]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AjouterNotification]
    @id_employe INT,
    @id_reunion INT,
    @type_notification VARCHAR(100),
    @message NVARCHAR(1000),
    @date_envoi DATETIME,
    @status VARCHAR(50)
AS
BEGIN
    DECLARE @id_notification INT;

    INSERT INTO Notifications (type_notification, message)
    VALUES (@type_notification, @message);

    SET @id_notification = SCOPE_IDENTITY();

    INSERT INTO Notifications_Invitations (id_employe, id_reunion, id_notification, date_envoi, status)
    VALUES (@id_employe, @id_reunion, @id_notification, @date_envoi, @status);
END;
GO
/****** Object:  StoredProcedure [dbo].[AjouterReunion]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AjouterReunion]
    @id_hote INT,
    @id_salle INT,
    @ordre_jour NVARCHAR(500),
    @date_debut DATETIME,
    @duree INT,
    @lien VARCHAR(255),
    @type_reunion VARCHAR(50)
AS
BEGIN
    INSERT INTO Reunions (id_hote, id_salle, ordre_jour, date_debut, duree, lien, type_reunion)
    VALUES (@id_hote, @id_salle, @ordre_jour, @date_debut, @duree, @lien, @type_reunion);
END;
GO
/****** Object:  StoredProcedure [dbo].[GenererRapportReunions]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GenererRapportReunions]
AS
BEGIN
    DECLARE @id_employe INT;
    DECLARE @nom_employe VARCHAR(255);
    DECLARE @nombre_reunions INT;

    -- Déclarer le curseur
    DECLARE employe_cursor CURSOR FOR
    SELECT E.id_employe, E.nom + ' ' + E.prenom AS nom_employe, COUNT(I.id_reunion) AS nombre_reunions
    FROM Employes E
    LEFT JOIN Invitations I ON E.id_employe = I.id_employe
    GROUP BY E.id_employe, E.nom, E.prenom;

    -- Ouvrir le curseur
    OPEN employe_cursor;

    -- Parcourir les lignes
    FETCH NEXT FROM employe_cursor INTO @id_employe, @nom_employe, @nombre_reunions;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        -- Afficher ou enregistrer le rapport
        PRINT 'Employé : ' + @nom_employe + ', Nombre de réunions : ' + CAST(@nombre_reunions AS VARCHAR);

        -- Ligne suivante
        FETCH NEXT FROM employe_cursor INTO @id_employe, @nom_employe, @nombre_reunions;
    END;

    -- Fermer et libérer le curseur
    CLOSE employe_cursor;
    DEALLOCATE employe_cursor;
END;

GO
/****** Object:  StoredProcedure [dbo].[GetEmployeInvite]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetEmployeInvite]
    @id_reunion INT
AS
BEGIN
    SELECT E.*
    FROM Employes E
    INNER JOIN Invitations I ON E.id_employe = I.id_employe
    WHERE I.id_reunion = @id_reunion;
END;

GO
/****** Object:  StoredProcedure [dbo].[GetEmployeNotifications]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetEmployeNotifications]
    @id_employe INT
AS
BEGIN
    SELECT N.*
    FROM Notifications N
    INNER JOIN Notifications_Invitations NI ON N.id_notification = NI.id_notification
    WHERE NI.id_employe = @id_employe;
END;
GO
/****** Object:  StoredProcedure [dbo].[GetReunionDocuments]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetReunionDocuments]
    @id_reunion INT
AS
BEGIN
    SELECT D.*
    FROM Documents D
    INNER JOIN Reunions_Documents RD ON D.id_document = RD.id_document
    WHERE RD.id_reunion = @id_reunion;
END
GO
/****** Object:  StoredProcedure [dbo].[GetReunionsAvenir]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetReunionsAvenir]
AS
BEGIN
    SELECT *
    FROM Reunions
    WHERE date_debut > GETDATE();
END;
GO
/****** Object:  StoredProcedure [dbo].[GetReunionsParEmploye]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetReunionsParEmploye]
    @id_employe INT
AS
BEGIN
    SELECT R.*
    FROM Reunions R
    INNER JOIN Invitations I ON R.id_reunion = I.id_reunion
    WHERE I.id_employe = @id_employe;
END;
GO
/****** Object:  StoredProcedure [dbo].[GetReunionsParHote]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetReunionsParHote]
    @id_hote INT
AS
BEGIN
    SELECT *
    FROM Reunions
    WHERE id_hote = @id_hote;
END;

GO
/****** Object:  StoredProcedure [dbo].[GetReunionsParSalle]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetReunionsParSalle]
    @id_salle INT
AS
BEGIN
    SELECT *
    FROM Reunions
    WHERE id_salle = @id_salle;
END;
GO
/****** Object:  StoredProcedure [dbo].[GetReunionsParType]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetReunionsParType]
    @type_reunion VARCHAR(50)
AS
BEGIN
    SELECT *
    FROM Reunions
    WHERE type_reunion = @type_reunion;
END;
GO
/****** Object:  StoredProcedure [dbo].[Invite]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[Invite]
    @id_employe INT,
    @id_reunion INT,
    @disponibilite VARCHAR(50),
    @presence VARCHAR(20),
    @type_participation VARCHAR(50)
AS
BEGIN
    INSERT INTO Invitations (id_employe, id_reunion, disponibilite, presence, type_participation)
    VALUES (@id_employe, @id_reunion, @disponibilite, @presence, @type_participation);
END;
GO
/****** Object:  StoredProcedure [dbo].[MarquerPresence]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[MarquerPresence]
    @id_employe INT,
    @id_reunion INT,
    @presence VARCHAR(50)
AS
BEGIN
    UPDATE Invitations
    SET presence = @presence
    WHERE id_employe = @id_employe AND id_reunion = @id_reunion;
END;
GO
/****** Object:  StoredProcedure [dbo].[ModifierDisponibilite]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[ModifierDisponibilite]
    @id_employe INT,
    @id_reunion INT,
    @disponibilite VARCHAR(50)
AS
BEGIN
    UPDATE Invitations
    SET disponibilite = @disponibilite
    WHERE id_employe = @id_employe AND id_reunion = @id_reunion;
END;
GO
/****** Object:  StoredProcedure [dbo].[ModifierReunion]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[ModifierReunion]
    @id_reunion INT,
    @id_hote INT,
    @id_salle INT,
    @ordre_jour NVARCHAR(500),
    @date_debut DATETIME,
    @duree INT,
    @lien VARCHAR(255),
    @type_reunion VARCHAR(50)
AS
BEGIN
    UPDATE Reunions
    SET id_hote = @id_hote,
        id_salle = @id_salle,
        ordre_jour = @ordre_jour,
        date_debut = @date_debut,
        duree = @duree,
        lien = @lien,
        type_reunion = @type_reunion
    WHERE id_reunion = @id_reunion;
END;

GO
/****** Object:  StoredProcedure [dbo].[SupprimerDocumentReunion]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[SupprimerDocumentReunion]
    @id_document INT,
    @id_reunion INT
AS
BEGIN
    DELETE FROM Reunions_Documents
    WHERE id_document = @id_document AND id_reunion = @id_reunion;
END;
GO
/****** Object:  StoredProcedure [dbo].[SupprimerReunion]    Script Date: 3/24/2025 11:48:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[SupprimerReunion]
    @id_reunion INT
AS
BEGIN

    DELETE FROM Notifications_Invitations WHERE id_reunion = @id_reunion;
    DELETE FROM Invitations WHERE id_reunion = @id_reunion;
    DELETE FROM Reunions_Documents WHERE id_reunion = @id_reunion;
    DELETE FROM Compte_Rendu WHERE id_reunion = @id_reunion;
    
    DELETE FROM Reunions WHERE id_reunion = @id_reunion;
END;
GO
USE [master]
GO
ALTER DATABASE [GESTION_REUNION] SET  READ_WRITE 
GO
