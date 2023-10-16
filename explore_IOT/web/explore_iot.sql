-- phpMyAdmin SQL Dump
-- version 4.9.5deb2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Apr 11, 2022 at 12:13 PM
-- Server version: 10.3.34-MariaDB-0ubuntu0.20.04.1
-- PHP Version: 7.4.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `explore_iot`
--

-- --------------------------------------------------------

--
-- Table structure for table `sensor_anemometer`
--

CREATE TABLE `sensor_anemometer` (
  `id` int(11) NOT NULL,
  `data_anemometer` float NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `sensor_anemometer`
--

INSERT INTO `sensor_anemometer` (`id`, `data_anemometer`, `created_at`, `updated_at`) VALUES
(2, 4, '2021-09-29 01:54:36', '2021-09-29 01:54:36'),
(3, 3, '2021-10-08 18:25:04', '2021-10-08 18:25:04');

-- --------------------------------------------------------

--
-- Table structure for table `sensor_baterai`
--

CREATE TABLE `sensor_baterai` (
  `id` int(11) NOT NULL,
  `data_baterai` float NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `sensor_baterai`
--

INSERT INTO `sensor_baterai` (`id`, `data_baterai`, `created_at`, `updated_at`) VALUES
(1, 12.3, '2021-09-25 01:29:57', '2021-09-25 01:29:57'),
(2, 11.7, '2021-09-29 01:50:02', '2021-09-29 01:50:02'),
(3, 13, '2021-09-28 14:41:09', '2021-09-28 14:41:09');

-- --------------------------------------------------------

--
-- Table structure for table `sensor_ina1`
--

CREATE TABLE `sensor_ina1` (
  `id` int(11) NOT NULL,
  `data_volt` float NOT NULL,
  `data_arus` float NOT NULL,
  `data_daya` float NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `sensor_ina1`
--

INSERT INTO `sensor_ina1` (`id`, `data_volt`, `data_arus`, `data_daya`, `created_at`, `updated_at`) VALUES
(1, 12.7, 0, 0, '2021-09-24 14:08:12', '2021-09-24 14:08:12'),
(2, 12.8, 5.7, 0, '2021-09-24 14:22:50', '2021-09-24 14:22:50'),
(3, 2, 0, 0, '2021-09-28 02:43:42', '2021-09-28 02:43:42'),
(4, 2, 2, 0, '2021-09-28 02:54:21', '2021-09-28 02:54:21'),
(5, 2, 2, 0, '2021-09-28 02:55:04', '2021-09-28 02:55:04'),
(6, 2, 2, 0, '2021-09-28 02:55:35', '2021-09-28 02:55:35'),
(8, 10, 2, 0, '2021-09-28 02:57:38', '2021-09-28 02:57:38'),
(11, 12, 3, 0, '2021-09-28 14:39:26', '2021-09-28 14:39:26'),
(12, 12.3, 2, 0, '2021-10-03 23:48:00', '2021-10-03 23:48:00'),
(13, 12.3, 2, 0, '2021-10-03 23:48:05', '2021-10-03 23:48:05'),
(14, 12.3, 2, 0, '2021-10-03 23:48:07', '2021-10-03 23:48:07'),
(15, 12.3, 2, 0, '2021-10-03 23:48:09', '2021-10-03 23:48:09'),
(16, 12.3, 2, 0, '2021-10-03 23:48:10', '2021-10-03 23:48:10'),
(17, 12, 2, 4, '2022-04-04 17:59:04', '2022-04-04 17:59:04');

-- --------------------------------------------------------

--
-- Table structure for table `sensor_ina2`
--

CREATE TABLE `sensor_ina2` (
  `id` int(11) NOT NULL,
  `data_volt` float NOT NULL,
  `data_arus` float NOT NULL,
  `data_daya` float NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `sensor_ina2`
--

INSERT INTO `sensor_ina2` (`id`, `data_volt`, `data_arus`, `data_daya`, `created_at`, `updated_at`) VALUES
(3, 8, 3, 0, '2021-10-08 15:06:29', '2021-10-08 15:06:29'),
(4, 8, 2, 0, '2021-10-08 15:06:33', '2021-10-08 15:06:33'),
(5, 4, 2, 0, '2021-10-08 15:06:40', '2021-10-08 15:06:40'),
(6, 6, 2, 0, '2021-10-08 15:06:44', '2021-10-08 15:06:44'),
(7, 12, 2, 4, '2022-04-04 17:59:50', '2022-04-04 17:59:50');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `nama` varchar(60) NOT NULL,
  `username` varchar(60) NOT NULL,
  `email` varchar(50) NOT NULL,
  `permision` varchar(50) NOT NULL,
  `password` varchar(100) NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `nama`, `username`, `email`, `permision`, `password`, `created_at`, `updated_at`) VALUES
(2, 'Muhammad Taufikurrahman', 'admin', 'narataufikurrahman@gmail.com', 'admin', '$2y$10$BOYoO9w3/NYWOF3Cz5M1AeAHbzcBeLjOfXpYL6zN0w66ikhPpHjCG', '2021-10-09 13:22:51', '2021-10-10 22:03:56'),
(3, 'Tamu Explore-IoT', 'user', 'user@gmail.com', 'user', '$2y$10$edoJ2sHNXb959DrqT6FElelIKeA8TNU.WeMqWdjukR.FzQ5J1AanS', '2021-10-09 13:28:55', '2021-10-10 22:03:59'),
(7, 'baitur', 'baeitur', 'baeiturj@gmail.com', 'user', '$2y$10$3YGk5.H.lOTg0be0upmLAerOFnEWFW/GnM30JPQDKg1siUQqKLUSC', '2022-04-10 16:48:49', '2022-04-10 16:49:28');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `sensor_anemometer`
--
ALTER TABLE `sensor_anemometer`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor_baterai`
--
ALTER TABLE `sensor_baterai`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor_ina1`
--
ALTER TABLE `sensor_ina1`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor_ina2`
--
ALTER TABLE `sensor_ina2`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `sensor_anemometer`
--
ALTER TABLE `sensor_anemometer`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `sensor_baterai`
--
ALTER TABLE `sensor_baterai`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `sensor_ina1`
--
ALTER TABLE `sensor_ina1`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT for table `sensor_ina2`
--
ALTER TABLE `sensor_ina2`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
