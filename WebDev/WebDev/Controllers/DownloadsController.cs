using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using WebDev.DAL;

namespace WebDev.Controllers
{
    public class DownloadsController : Controller
    {
        // GET: Downloads
        public ActionResult Index()
        {
            return View();
        }

        [Authorize]
        // GET: Downloads/Download
        public ActionResult Download()
        {
            /*WebDevContext db = new WebDevContext();
            var download = db.Downloads.Find(1);
            download.quantity++;
            db.SaveChanges();*/
            Response.Redirect("/App_Data/app.zip");
            return View();
        }
    }
}