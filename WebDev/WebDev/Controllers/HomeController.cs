using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebDev.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            //WebDev.DAL.WebDevContext db = new WebDev.DAL.WebDevContext();
            //var s = from u in db.Sounds select u;
            //var t = from u in db.Textures select u;
            return View();
        }
    }
}