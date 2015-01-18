using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebDev.Controllers
{
    [Authorize]
    public class TextureViewerController : Controller
    {
        // GET: TextureViewer
        public ActionResult Index()
        {
            return View();
        }
    }
}