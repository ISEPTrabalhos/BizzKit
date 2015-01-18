using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;
using WebDev.DAL;
using WebDev.Models;

namespace WebDev.Controllers
{
    [Authorize]
    public class GameRoutesController : Controller
    {
        private WebDevContext db = new WebDevContext();

        // GET: GameRoutes
        public ActionResult Index()
        {
            string name = User.Identity.Name;
            var routes = from r in db.GameRoute
                         where r.username == name
                         select r;

            return View(routes.ToList());
        }

        // GET: GameRoutes/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            GameRoute gameRoute = db.GameRoute.Find(id);
            if (gameRoute == null)
            {
                return HttpNotFound();
            }
            return View(gameRoute);
        }

        // POST: GameRoutes/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            GameRoute gameRoute = db.GameRoute.Find(id);
            db.GameRoute.Remove(gameRoute);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}
