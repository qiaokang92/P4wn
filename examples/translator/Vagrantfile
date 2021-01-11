Vagrant.configure("2") do |config|
	config.vm.box = "ubuntu/xenial64"
	config.disksize.size = "32GB"
  
	config.vm.provider "virtualbox" do |vb|
	#   # Display the VirtualBox GUI when booting the machine
	#   vb.gui = true
	#
	#   # Customize the amount of memory on the VM:
		vb.memory = "4096"
	end
	
	config.vm.provision :shell, path: "setup.sh", keep_color: true, privileged: false
	#config.vm.provision "file", source: ".profile", destination: "~/.profile"
end