-- MySQL dump 10.13  Distrib 5.7.21, for Linux (x86_64)
--
-- Host: localhost    Database: controlAccesos
-- ------------------------------------------------------
-- Server version	5.7.21-0ubuntu0.16.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Grupos`
--

DROP TABLE IF EXISTS `Grupos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Grupos` (
  `IdGrupo` varchar(6) NOT NULL,
  `Nombre` varchar(20) NOT NULL,
  `Permiso` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`IdGrupo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Grupos`
--

LOCK TABLES `Grupos` WRITE;
/*!40000 ALTER TABLE `Grupos` DISABLE KEYS */;
INSERT INTO `Grupos` VALUES ('1ESOA','1º ESO A',0),('2BACHA','2º Bachiller A',1);
/*!40000 ALTER TABLE `Grupos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Registro`
--

DROP TABLE IF EXISTS `Registro`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Registro` (
  `IdRegistro` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `Usuario` varchar(8) NOT NULL,
  `EntradaSalida` tinyint(1) NOT NULL DEFAULT '1',
  `FechaHora` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`IdRegistro`),
  KEY `Usuario` (`Usuario`),
  CONSTRAINT `Registro_ibfk_1` FOREIGN KEY (`Usuario`) REFERENCES `Usuarios` (`TagRFID`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Registro`
--

LOCK TABLES `Registro` WRITE;
/*!40000 ALTER TABLE `Registro` DISABLE KEYS */;
INSERT INTO `Registro` VALUES (1,'9AFB24C9',1,'2018-06-02 20:45:10'),(2,'D3419055',1,'2018-06-02 20:45:26'),(3,'9AFB24C9',0,'2018-06-02 20:45:39'),(5,'AABBCCDD',1,'2018-06-03 07:00:04'),(6,'AABBCCDD',1,'2018-06-03 07:27:04'),(7,'AABBCCDD',1,'2018-06-03 07:44:12'),(8,'9AFB24C9',1,'2018-06-03 18:26:39'),(9,'9AFB24C9',1,'2018-06-03 18:40:00');
/*!40000 ALTER TABLE `Registro` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Usuarios`
--

DROP TABLE IF EXISTS `Usuarios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Usuarios` (
  `TagRFID` varchar(8) NOT NULL,
  `Nombre` varchar(20) NOT NULL,
  `Apellidos` varchar(40) NOT NULL,
  `Activo` tinyint(1) NOT NULL DEFAULT '1',
  `Staff` tinyint(1) NOT NULL DEFAULT '0',
  `Grupo` varchar(6) NOT NULL,
  `Email` varchar(50) NOT NULL,
  PRIMARY KEY (`TagRFID`),
  KEY `Grupo` (`Grupo`),
  CONSTRAINT `Usuarios_ibfk_1` FOREIGN KEY (`Grupo`) REFERENCES `Grupos` (`IdGrupo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Usuarios`
--

LOCK TABLES `Usuarios` WRITE;
/*!40000 ALTER TABLE `Usuarios` DISABLE KEYS */;
INSERT INTO `Usuarios` VALUES ('9AFB24C9','Alumno2','Alumno Dos',1,0,'2BACHA','alumno2@iespenyagolosa.es'),('AABBCCDD','Alumnox','Alumno X',1,0,'2BACHA','alumnox@iespenyagolosa.es'),('D3419055','Alumno1','Alumno Uno',1,0,'1ESOA','alumno1@iespenyagolosa.es');
/*!40000 ALTER TABLE `Usuarios` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-06-04 13:14:22
