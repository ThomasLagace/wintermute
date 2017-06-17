#pragma once
#pragma once
#include <k5/k5.h>

class ModelFrame : public IFrame {

public:
	virtual void Init(CEngine* e) override;
	virtual void Cleanup() override;

	virtual void Pause() override;
	virtual void Resume() override;

	virtual void ProcessInput(bool* keyboard, bool* mouse, double mxpos, double mypos) override;
	virtual void Loop() override;
	virtual void Render() override;

	static ModelFrame& Instance() {
		static ModelFrame instance;
		return instance;
	}

protected:
	ModelFrame() = default;
	ModelFrame(const ModelFrame&) = delete;
	ModelFrame(ModelFrame&&) = delete;
	void operator=(const ModelFrame&) = delete;
	void operator=(ModelFrame&&) = delete;

private:

	CEngine* engine;
};