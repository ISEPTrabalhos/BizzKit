using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Mvc;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using WebDev;
using WebDev.Controllers;

namespace WebDev.Tests.Controllers
{
    [TestClass]
    public class ScoresControllerTest
    {
        [TestMethod]
        public void Index()
        {
            // Arrange
            ScoresController controller = new ScoresController();

            // Act
            ViewResult result = controller.Index() as ViewResult;

            // Assert
            Assert.IsNotNull(result);
        }
    }
}
