using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;
using WebDev.Services;

namespace WebDev.Tests.Services
{
    [TestClass]
    public class ServiceTest
    {
        [TestMethod]
        public void Login()
        {
            // Arrange
            Service service = new Service();

            // Act
            int result = service.Login("admin", "Admin_123");

            // Assert
            Assert.AreEqual(result, 1);
        }

        [TestMethod]
        public void Score()
        {
            
        }

        [TestMethod]
        public void ListLevels()
        {
            // Arrange
            Service service = new Service();

            // Act
            string result = service.ListLevels();

            // Assert
            Assert.IsNotNull(result);
            
        }

        [TestMethod]
        public void getTexturesList()
        {
            // Arrange
            Service service = new Service();

            // Act
            string result = service.getTexturesList();

            // Assert
            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void getSoundsList()
        {
            // Arrange
            Service service = new Service();

            // Act
            string result = service.getSoundsList();

            // Assert
            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void downloadSound()
        {
            
        }

        [TestMethod]
        public void uploadRoute()
        {
            
        }

        [TestMethod]
        public void getEnemiesModelsList()
        {
            // Arrange
            Service service = new Service();

            // Act
            string result = service.getEnemiesModelsList();

            // Assert
            Assert.IsNotNull(result);
        }

        [TestMethod]
        public void DownloadEnemiesModels()
        {
            
        }
    }
}
