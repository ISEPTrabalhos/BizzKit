using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebDev.Models
{
    public class Downloads
    {
        [Key]
        public int ID { get; set; }

        [Required]
        public string fileName { get; set; }

        public int quantity;
    }
}