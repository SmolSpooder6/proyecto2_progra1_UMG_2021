CREATE DATABASE  IF NOT EXISTS `proyecto2_db` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `proyecto2_db`;
-- MySQL dump 10.13  Distrib 8.0.24, for Win64 (x86_64)
--
-- Host: localhost    Database: proyecto2_db
-- ------------------------------------------------------
-- Server version	8.0.24

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `clientes`
--

DROP TABLE IF EXISTS `clientes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `clientes` (
  `idClientes` int NOT NULL AUTO_INCREMENT,
  `nombres` varchar(60) DEFAULT NULL,
  `apellidos` varchar(60) DEFAULT NULL,
  `nit` varchar(12) DEFAULT NULL,
  `genero` bit(1) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  `correo_electronico` varchar(45) DEFAULT NULL,
  `fechaIngreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idClientes`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `clientes`
--

LOCK TABLES `clientes` WRITE;
/*!40000 ALTER TABLE `clientes` DISABLE KEYS */;
INSERT INTO `clientes` VALUES (0,'c/f','c/f','c/f',_binary '','c/f','c/f','2021-05-10 00:00:00'),(11,'pedro jose','castillo','nit2',_binary '','87654321','pjc','2021-05-11 00:00:00'),(13,'jose luis','perez','nit4',_binary '','654','jlp','2021-05-13 00:00:00'),(14,'edgar jose','perez','nit5',_binary '','789','ejp','2021-05-14 00:00:00'),(15,'Maria Jose','castillo perez','nit6',_binary '\0','369','mjc','2021-05-16 14:34:02'),(16,'Juan Pedro','Morales Juarez','nit7',_binary '','753','JPMJ@mail.com','2021-05-15 12:25:02'),(17,'Jessica','Morales Perez','nit8',_binary '\0','5511','jmp','2021-05-26 23:08:47'),(21,'Gerardo','Castillo','abc',_binary '','5566','gggg','2021-05-27 00:35:10'),(22,'asd','fds','bsd',_binary '','456','qwer','2021-05-27 17:45:45'),(23,'Juanito','Perez','qwertt',_binary '','8899','Juanito@mail.com','2021-05-27 18:09:48'),(24,'Juan Jose','Castro','nit9',_binary '','1234','jjc@mail.com','2021-06-08 12:31:17'),(25,'Karla Sofia','Castro Juarez','123',_binary '\0','5555','KSCJ@mail.com','2021-06-08 14:35:32'),(26,'jose','cobian','2011532',_binary '\0','0','asdf','2021-06-08 19:14:53'),(27,' jose','cobian','.32361311',_binary '','1564544',' masndajn@gmail.com','2021-06-08 19:16:16');
/*!40000 ALTER TABLE `clientes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `compras`
--

DROP TABLE IF EXISTS `compras`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `compras` (
  `idcompras` int NOT NULL AUTO_INCREMENT,
  `no_orden_compra` int DEFAULT NULL,
  `idProveedor` int DEFAULT NULL,
  `fecha_orden` date DEFAULT NULL,
  `fechaIngreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idcompras`),
  KEY `idproveedor_proveedores_compras_idx` (`idProveedor`),
  CONSTRAINT `idproveedor_proveedores_compras` FOREIGN KEY (`idProveedor`) REFERENCES `proveedores` (`idproveedores`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `compras`
--

LOCK TABLES `compras` WRITE;
/*!40000 ALTER TABLE `compras` DISABLE KEYS */;
INSERT INTO `compras` VALUES (1,1,3,'2021-06-07','2021-06-07 13:17:41'),(2,2,3,'2021-06-07','2021-06-07 18:21:15'),(3,3,3,'2021-06-07','2021-06-07 18:30:42'),(4,4,3,'2021-06-07','2021-06-07 18:33:34'),(6,6,3,'2021-06-07','2021-06-07 20:37:13'),(7,8,3,'2021-06-07','2021-06-07 20:39:32'),(8,9,4,'2021-06-08','2021-06-08 21:23:19'),(9,10,4,'2021-06-08','2021-06-08 21:28:26');
/*!40000 ALTER TABLE `compras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `compras_detalle`
--

DROP TABLE IF EXISTS `compras_detalle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `compras_detalle` (
  `idcompras_detalle` bigint NOT NULL AUTO_INCREMENT,
  `idcompra` int DEFAULT NULL,
  `idproducto` int DEFAULT NULL,
  `cantidad` int DEFAULT NULL,
  `precio_costo_unitario` decimal(8,2) DEFAULT NULL,
  PRIMARY KEY (`idcompras_detalle`),
  KEY `idcompra_compras_comprasDetalle_idx` (`idcompra`),
  KEY `idproducto_productos_comprasDetalle_idx` (`idproducto`),
  CONSTRAINT `idcompra_compras_comprasDetalle` FOREIGN KEY (`idcompra`) REFERENCES `compras` (`idcompras`) ON UPDATE CASCADE,
  CONSTRAINT `idproducto_productos_comprasDetalle` FOREIGN KEY (`idproducto`) REFERENCES `productos` (`idProducto`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `compras_detalle`
--

LOCK TABLES `compras_detalle` WRITE;
/*!40000 ALTER TABLE `compras_detalle` DISABLE KEYS */;
INSERT INTO `compras_detalle` VALUES (6,7,1,10,20.12),(7,8,3,11,50.92);
/*!40000 ALTER TABLE `compras_detalle` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `empleados`
--

DROP TABLE IF EXISTS `empleados`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `empleados` (
  `idempleados` int NOT NULL AUTO_INCREMENT,
  `nombres` varchar(60) DEFAULT NULL,
  `apellidos` varchar(60) DEFAULT NULL,
  `direccion` varchar(80) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  `DPI` varchar(15) DEFAULT NULL,
  `genero` bit(1) DEFAULT NULL,
  `fecha_nacimiento` date DEFAULT NULL,
  `idPuesto` smallint DEFAULT NULL,
  `fecha_inicio_labores` date DEFAULT NULL,
  `fechaIngreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idempleados`),
  KEY `idPuesto_puestos_empleados_idx` (`idPuesto`),
  CONSTRAINT `idPuesto_puestos_empleados` FOREIGN KEY (`idPuesto`) REFERENCES `puestos` (`idPuesto`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `empleados`
--

LOCK TABLES `empleados` WRITE;
/*!40000 ALTER TABLE `empleados` DISABLE KEYS */;
INSERT INTO `empleados` VALUES (11,'Juan Manuel','Sanchez Juarez','ciudad','111','222',_binary '','1995-05-05',5,'2021-05-17','2021-05-17 22:47:40'),(12,'Juan Jose','Perez Sanchez','ciudad','123','321',_binary '','1995-05-05',4,'2021-05-17','2021-05-17 22:47:40'),(13,'Pedro Juan','zamora gonsalez','ciudad','25896321','7896',_binary '','1995-05-20',4,'2021-05-20','2021-05-20 15:44:51'),(15,'Ana Maria','Lux del Cid','Ciudad','555','333',_binary '\0','1990-05-05',6,'2021-06-10','2021-06-08 16:17:46');
/*!40000 ALTER TABLE `empleados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `marcas`
--

DROP TABLE IF EXISTS `marcas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `marcas` (
  `idMarca` smallint NOT NULL AUTO_INCREMENT,
  `marca` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idMarca`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `marcas`
--

LOCK TABLES `marcas` WRITE;
/*!40000 ALTER TABLE `marcas` DISABLE KEYS */;
INSERT INTO `marcas` VALUES (2,'Marca2'),(3,'opc1'),(4,'opc2'),(5,'marca3');
/*!40000 ALTER TABLE `marcas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `productos`
--

DROP TABLE IF EXISTS `productos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `productos` (
  `idProducto` int NOT NULL AUTO_INCREMENT,
  `producto` varchar(50) DEFAULT NULL,
  `idMarca` smallint DEFAULT NULL,
  `Descripcion` varchar(100) DEFAULT NULL,
  `Imagen` varchar(30) DEFAULT NULL,
  `precio_costo` decimal(8,2) DEFAULT NULL,
  `precio_venta` decimal(8,2) DEFAULT NULL,
  `existencia` int DEFAULT NULL,
  `fecha_ingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idProducto`),
  KEY `idMarca_marcas_productos_idx` (`idMarca`),
  CONSTRAINT `idMarca_marcas_productos` FOREIGN KEY (`idMarca`) REFERENCES `marcas` (`idMarca`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `productos`
--

LOCK TABLES `productos` WRITE;
/*!40000 ALTER TABLE `productos` DISABLE KEYS */;
INSERT INTO `productos` VALUES (1,'pro1',2,'desc1','IMG',20.12,30.12,10,'2021-05-19 13:51:41'),(2,'pro2',3,'desc2','img2',22.50,35.20,10,'2021-05-19 19:24:58'),(3,'pro3',4,'desc3','img3',50.92,100.99,11,'2021-05-19 13:51:41');
/*!40000 ALTER TABLE `productos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proveedores`
--

DROP TABLE IF EXISTS `proveedores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `proveedores` (
  `idproveedores` int NOT NULL AUTO_INCREMENT,
  `proveedor` varchar(60) DEFAULT NULL,
  `nit` varchar(12) DEFAULT NULL,
  `direccion` varchar(80) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`idproveedores`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proveedores`
--

LOCK TABLES `proveedores` WRITE;
/*!40000 ALTER TABLE `proveedores` DISABLE KEYS */;
INSERT INTO `proveedores` VALUES (3,'pro2','888','antigua','999'),(4,'proveedor 3','555','Ciudad','444');
/*!40000 ALTER TABLE `proveedores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `puestos`
--

DROP TABLE IF EXISTS `puestos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `puestos` (
  `idPuesto` smallint NOT NULL AUTO_INCREMENT,
  `puesto` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idPuesto`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `puestos`
--

LOCK TABLES `puestos` WRITE;
/*!40000 ALTER TABLE `puestos` DISABLE KEYS */;
INSERT INTO `puestos` VALUES (4,'Gerente'),(5,'Jefe'),(6,'Asistente');
/*!40000 ALTER TABLE `puestos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ventas`
--

DROP TABLE IF EXISTS `ventas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ventas` (
  `idVentas` int NOT NULL AUTO_INCREMENT,
  `noFactura` int DEFAULT NULL,
  `serie` char(1) DEFAULT NULL,
  `fechaFactura` date DEFAULT NULL,
  `idcliente` int DEFAULT NULL,
  `idempleado` int DEFAULT NULL,
  `fechaIngreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idVentas`),
  KEY `idcliente_clientes_ventas_idx` (`idcliente`),
  KEY `idempleados_clientes_ventas_idx` (`idempleado`),
  CONSTRAINT `idcliente_clientes_ventas` FOREIGN KEY (`idcliente`) REFERENCES `clientes` (`idClientes`) ON UPDATE CASCADE,
  CONSTRAINT `idempleados_clientes_ventas` FOREIGN KEY (`idempleado`) REFERENCES `empleados` (`idempleados`)
) ENGINE=InnoDB AUTO_INCREMENT=65 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ventas`
--

LOCK TABLES `ventas` WRITE;
/*!40000 ALTER TABLE `ventas` DISABLE KEYS */;
INSERT INTO `ventas` VALUES (41,1,'e','2021-06-03',0,11,'2021-06-03 01:30:23'),(42,2,'e','2021-06-03',0,11,'2021-06-03 01:33:33'),(43,3,'e','2021-06-03',0,11,'2021-06-03 01:35:22'),(44,4,'e','2021-06-03',0,11,'2021-06-03 01:49:17'),(45,5,'e','2021-06-03',0,11,'2021-06-03 01:51:52'),(46,6,'e','2021-06-03',0,11,'2021-06-03 01:54:11'),(47,7,'e','2021-06-03',0,11,'2021-06-03 02:01:43'),(48,8,'e','2021-06-03',0,11,'2021-06-03 02:04:31'),(49,9,'e','2021-06-03',0,11,'2021-06-03 02:06:40'),(51,10,'e','2021-06-03',0,11,'2021-06-03 02:11:44'),(52,11,'e','2021-06-03',0,11,'2021-06-03 02:15:11'),(53,12,'e','2021-06-03',0,11,'2021-06-03 02:17:59'),(54,13,'e','2021-06-03',0,12,'2021-06-03 02:27:11'),(56,14,'e','2021-06-03',11,11,'2021-06-03 11:55:52'),(57,15,'e','2021-06-03',15,12,'2021-06-03 12:02:11'),(58,16,'e','2021-06-03',16,13,'2021-06-03 12:11:01'),(60,18,'e','2021-06-03',15,11,'2021-06-03 12:20:57'),(61,19,'e','2021-06-03',13,11,'2021-06-03 13:08:06'),(62,20,'e','2021-06-03',15,11,'2021-06-03 13:13:39'),(63,21,'e','2021-06-03',15,11,'2021-06-03 13:31:15');
/*!40000 ALTER TABLE `ventas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ventas_detalle`
--

DROP TABLE IF EXISTS `ventas_detalle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ventas_detalle` (
  `idventa_detalle` bigint NOT NULL AUTO_INCREMENT,
  `idVenta` int DEFAULT NULL,
  `idProducto` int DEFAULT NULL,
  `cantidad` varchar(45) DEFAULT NULL,
  `precio_unitario` decimal(8,2) DEFAULT NULL,
  PRIMARY KEY (`idventa_detalle`),
  KEY `idVenta_ventas_ventasDetalle_idx` (`idVenta`),
  KEY `idProducto_producto_ventasDetalle_idx` (`idProducto`),
  CONSTRAINT `idProducto_producto_ventasDetalle` FOREIGN KEY (`idProducto`) REFERENCES `productos` (`idProducto`) ON UPDATE CASCADE,
  CONSTRAINT `idVenta_ventas_ventasDetalle` FOREIGN KEY (`idVenta`) REFERENCES `ventas` (`idVentas`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ventas_detalle`
--

LOCK TABLES `ventas_detalle` WRITE;
/*!40000 ALTER TABLE `ventas_detalle` DISABLE KEYS */;
INSERT INTO `ventas_detalle` VALUES (33,41,1,'1',30.99),(34,41,2,'2',35.20),(35,42,1,'2',30.99),(36,42,2,'1',35.20),(37,43,3,'2',100.99),(38,43,1,'1',30.99),(39,44,1,'2',30.99),(40,45,1,'2',30.99),(41,46,2,'2',35.20),(42,47,3,'2',100.99),(43,48,1,'2',30.99),(44,49,1,'2',30.99),(45,51,2,'2',35.20),(46,52,3,'2',100.99),(47,52,2,'3',35.20),(48,53,2,'3',35.20),(49,53,3,'2',100.99),(50,54,1,'2',30.99),(51,54,3,'2',100.99),(52,56,1,'2',30.99),(53,56,3,'3',100.99),(54,57,2,'3',35.20),(55,57,3,'1',100.99),(56,58,2,'2',35.20),(59,60,3,'1',100.99),(60,60,2,'2',35.20),(61,61,1,'2',30.99),(62,62,2,'2',35.20),(63,62,3,'1',100.99),(64,63,2,'3',35.20),(65,63,1,'2',30.99);
/*!40000 ALTER TABLE `ventas_detalle` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-06-08 22:10:00
