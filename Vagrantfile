$bootstrap = <<BOOTSTRAP
export DEBIAN_FRONTEND=noninteractive
apt-get update
apt-get -y install build-essential
apt-get -y install cmake valgrind lcov
apt-get -y install python3-pip
pip3 install gcovr
BOOTSTRAP

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/xenial32"

  # get rig of annoying console.log file 
  config.vm.provider "virtualbox" do |vb|
    vb.customize [ "modifyvm", :id, "--uartmode1", "disconnected" ]
  end

  # setup the VM
  config.vm.provision "shell", inline: $bootstrap
end

