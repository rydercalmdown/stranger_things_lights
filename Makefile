.PHONY: build
build:
	@docker-compose build

.PHONY: run
run:
	@docker-compose up

.PHONY: install-pi
install-pi:
	@cd scripts && bash install_raspberry_pi.sh

.PHONY: run-worker
run-worker:
	@. env/bin/activate && cd worker && python app.py
