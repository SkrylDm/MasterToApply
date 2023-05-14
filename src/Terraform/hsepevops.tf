terraform {
  required_providers {
    yandex = {
      source = "yandex-cloud/yandex"
    }
  }
  required_version = ">= 0.13"
}

provider "yandex" {
  token     = "yandex"
  cloud_id  = "0000"
  folder_id = "0000"
  zone      = "ru-central-b"
}

variable "ssh-key" {
  default = "yandex.pub"

}

resource "yandex_compute_instance" "vm-1" {
  name = "dev"
  platform_id = "standard-v1"
  zone = "ru-central1-b"
  resources {
    cores = "2"
    memory = "2"
  }

  network_interface {
  subnet_id = "${yandex_vpc_subnet.subnet-1.id}"
  nat = true
  }

  boot_disk {
    initialize_params {
      image_id = "fd8irfoscugmpsoanefh"
    }
  }

  metadata = {
    ssh-keys = "ubuntu:${file(var.ssh-key)}"
  }

  provisioner "remote-exec" {
   inline = [
      "sudo apt-get update && sudo apt-get install -y apache2"
   ]

   connection {
      type = "ssh" 
      user = "ubuntu"
      private_key = file("yandex")
      host = self.network_interface[0].nat_ip_address
      agent = "true"
    }
  }
}

resource "yandex_vpc_network" "network-1" {
  name = "devhsetask" 
}

resource "yandex_vpc_subnet" "subnet-1" {
  name           = "subnet1"
  zone           = "ru-central1-b"
  v4_cidr_blocks = ["192.116.10.0/24"]
  network_id     = "${yandex_vpc_network.network-1.id}"
}

resource "yandex_mdb_postgresql_cluster" "mypg" {
  name                = "mypg"
  environment         = "PRESTABLE"
  network_id          = yandex_vpc_network.network-1.id
  security_group_ids  = [ yandex_vpc_security_group.pgsql-sg.id ]
  deletion_protection = true

  config {
    version = 14
    resources {
      resource_preset_id = "s2.micro"
      disk_type_id       = "network-ssd"
      disk_size          = "20"
    }
  }

  host {
    zone      = "ru-central1-b"
    subnet_id = yandex_vpc_subnet.subnet-1.id
  }
}

resource "yandex_mdb_postgresql_database" "db1" {
  cluster_id = yandex_mdb_postgresql_cluster.mypg.id
  name       = "db1"
  owner      = "user1"
}

resource "yandex_mdb_postgresql_user" "user1" {
  cluster_id = yandex_mdb_postgresql_cluster.mypg.id
  name       = "user1"
  password   = "user1user1"
}

resource "yandex_vpc_security_group" "pgsql-sg" {
  name       = "pgsql-sg"
  network_id = yandex_vpc_network.network-1.id

  ingress {
    description    = "PostgreSQL"
    port           = 6432
    protocol       = "TCP"
    v4_cidr_blocks = [ "0.0.0.0/0" ]
  }
}

output "vm-ip" {
  value = yandex_compute_instance.vm-1.network_interface[0].nat_ip_address
}
