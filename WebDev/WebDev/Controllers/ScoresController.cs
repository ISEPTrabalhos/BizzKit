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
    public class ScoresController : Controller
    {
        private WebDevContext db = new WebDevContext();

        // GET: Scores
        public ActionResult Index()
        {
            var scores = db.Scores.Include(s => s.Level).Include(s => s.User);
            return View(scores.ToList());
        }

        // GET: Scores/Details/5
        public ActionResult Details(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Score score = db.Scores.Find(id);
            if (score == null)
            {
                return HttpNotFound();
            }
            return View(score);
        }

        // GET: Scores/Create
        public ActionResult Create()
        {
            ViewBag.levelName = new SelectList(db.Levels, "name", "content");
            ViewBag.username = new SelectList(db.Users, "username", "passwordHash");
            return View();
        }

        // POST: Scores/Create
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create([Bind(Include = "username,levelName,score")] Score score)
        {
            if (ModelState.IsValid)
            {
                db.Scores.Add(score);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.levelName = new SelectList(db.Levels, "name", "content", score.levelName);
            ViewBag.username = new SelectList(db.Users, "username", "passwordHash", score.username);
            return View(score);
        }

        // GET: Scores/Edit/5
        public ActionResult Edit(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Score score = db.Scores.Find(id);
            if (score == null)
            {
                return HttpNotFound();
            }
            ViewBag.levelName = new SelectList(db.Levels, "name", "content", score.levelName);
            ViewBag.username = new SelectList(db.Users, "username", "passwordHash", score.username);
            return View(score);
        }

        // POST: Scores/Edit/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "username,levelName,score")] Score score)
        {
            if (ModelState.IsValid)
            {
                db.Entry(score).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.levelName = new SelectList(db.Levels, "name", "content", score.levelName);
            ViewBag.username = new SelectList(db.Users, "username", "passwordHash", score.username);
            return View(score);
        }

        // GET: Scores/Delete/5
        public ActionResult Delete(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Score score = db.Scores.Find(id);
            if (score == null)
            {
                return HttpNotFound();
            }
            return View(score);
        }

        // POST: Scores/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(string id)
        {
            Score score = db.Scores.Find(id);
            db.Scores.Remove(score);
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
