Driver for an ethernet card: (see the approach and model of implementation)
----------------------------

<linux-source>/drivers/net/ethernet/<your-ethernet-card_vendor-name>/*

	ethernet details can be obtained from "lspci -v/vv" a shell command

	Ex:
	===
		linux-3.12/drivers/net/ethernet/realtek
